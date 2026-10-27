#!/usr/bin/env python3
"""
ulda_grid.py — 8-rib chain, 1 arithmetic veto.

Per claim:
  call 0   : agent proposes {phenomenon, reading, wave, observer, O, Q}
  gates 1–8: one LLM call per rib. Stateful — each sees prior outcomes.
             Any ✗ kills the chain; gates 4..8 never asked if 3 says ✗.
  veto     : engine computes chord_sqnorm(Q−O); if ≠ reading.expected,
             claim dies (killed_at[9]). Arithmetic is a veto, not a vote.

Final status = min over the 8 gates (order ✗ < ? < ~ < ✓), or dead.
"""

from __future__ import annotations

import json
import logging
import os
from dataclasses import dataclass
from enum import Enum
from typing import Callable, Optional

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
)
log = logging.getLogger(__name__)


# ===========================================================================
# §1 — ℤ[φ] arithmetic (exact, port of ulda.h)
# ===========================================================================

@dataclass(frozen=True)
class ZPhi:
    a: int
    b: int

    def __add__(self, o): return ZPhi(self.a + o.a, self.b + o.b)
    def __sub__(self, o): return ZPhi(self.a - o.a, self.b - o.b)
    def __mul__(self, o):
        ac = self.a * o.a; bd = self.b * o.b
        ad = self.a * o.b; bc = self.b * o.a
        return ZPhi(ac + bd, ad + bc + bd)

    def __str__(self): return f"{self.a} + {self.b}φ"


@dataclass(frozen=True)
class Vec3:
    x: ZPhi
    y: ZPhi
    z: ZPhi

    def __sub__(self, o): return Vec3(self.x - o.x, self.y - o.y, self.z - o.z)
    def sqnorm(self): return self.x * self.x + self.y * self.y + self.z * self.z

    @staticmethod
    def from_json(arr):
        return Vec3(ZPhi(*arr[0]), ZPhi(*arr[1]), ZPhi(*arr[2]))


def chord_sqnorm(O: Vec3, Q: Vec3) -> ZPhi:
    return (Q - O).sqnorm()


# ===========================================================================
# §2 — Grades (order: ✗ < ? < ~ < ✓)
# ===========================================================================

class Grade(Enum):
    REJECTED    = "✗"
    UNCONFIRMED = "?"
    PLAUSIBLE   = "~"
    CONFIRMED   = "✓"


_ORDER = {Grade.REJECTED: 0, Grade.UNCONFIRMED: 1,
          Grade.PLAUSIBLE: 2, Grade.CONFIRMED: 3}


# ===========================================================================
# §3 — Readings and observer
# ===========================================================================

class Reading(Enum):
    ROLLOVER = ("roll-over", ZPhi(7, 3))
    MIRROR   = ("mirror",    ZPhi(3, 1))
    LOOP     = ("loop",      ZPhi(5, 0))
    OFFSET   = ("offset",    ZPhi(1, 0))

    def __init__(self, label, expected):
        self.label = label
        self.expected = expected


WAVE_ALIASES = {
    "unassigned": 0, "-": 0, 0: 0,
    1: 1, "1": 1,
    3: 3, "3": 3,
    "3'": "3'", "3p": "3'", "3prime": "3'",
    4: 4, "4": 4,
    5: 5, "5": 5,
}

VALID_BASE60 = {0, 12, 24, 36, 48}


@dataclass(frozen=True)
class Observer:
    axis: int
    position: int
    turn: int
    base60: int


@dataclass
class Axis:
    reading: Reading
    wave: object
    observer: Observer


# ===========================================================================
# §4 — The 8 ribs (cube vertices, matching VERTICES[0..7])
# ===========================================================================

RIBS = [
    (1, 1, 1), (1, 1, -1), (1, -1, 1), (1, -1, -1),
    (-1, 1, 1), (-1, 1, -1), (-1, -1, 1), (-1, -1, -1),
]


# ===========================================================================
# §5 — Gates and chains
# ===========================================================================

@dataclass
class Gate:
    index: int
    rib: tuple[int, int, int]
    outcome: Grade
    evidence: str = ""

    def __post_init__(self):
        # Irrefutable outcomes require evidence.
        if self.outcome in (Grade.CONFIRMED, Grade.REJECTED) and not self.evidence:
            raise ValueError(
                f"gate {self.index}: {self.outcome.value} requires evidence"
            )


@dataclass
class Claim:
    phenomenon: str
    chain: list[Gate]
    axis: Axis
    O: Vec3
    Q: Vec3
    computed: ZPhi
    expected: ZPhi

    @property
    def status(self) -> Grade:
        return min((g.outcome for g in self.chain), key=_ORDER.get)

    @property
    def verified(self) -> bool:
        return self.computed == self.expected


# ===========================================================================
# §6 — The agent
# ===========================================================================

@dataclass
class Agent:
    name: str
    call: Callable[[str], str]
    context_budget: int = 200_000
    context_used: int = 0

    def invoke(self, prompt: str) -> str:
        if self.context_used >= self.context_budget:
            raise RuntimeError(f"{self.name} context exhausted.")
        self.context_used += len(prompt)
        return self.call(prompt)


# ===========================================================================
# §7 — Protocol
# ===========================================================================

PROPOSE_INSTRUCTION = """\
You are the ULDA agent. Propose ONE claim as JSON:

{
  "phenomenon": str,
  "reading": "roll-over"|"mirror"|"loop"|"offset",
  "wave": 1|3|"3'"|4|5,
  "observer": {"axis": 1..6, "position": ±1, "turn": 1|2, "base60": 0|12|24|36|48},
  "O": [[a,b],[a,b],[a,b]],   // ℤ[φ]³: a + bφ per coordinate
  "Q": [[a,b],[a,b],[a,b]],
  "ground": str
}
"""

GATE_INSTRUCTION = """\
You are the ULDA agent, at gate {index} of 8. The claim is:
{claim}

Prior gates:
{prior}

Does this claim pass through rib ({sx}, {sy}, {sz})?

Reply with EXACTLY:
  {"outcome": "✓"|"~"|"?"|"✗", "evidence": "..."}

Rules:
  - "?" is the default. Use it if no evidence either way.
  - "~" only if you have soft/suggestive evidence.
  - "✓" or "✗" require IRREFUTABLE evidence — else use "~" or "?".
  - Do not change a "~" to "✓" without new evidence.
"""


class Method:
    def __init__(self, agent: Agent) -> None:
        self.agent = agent
        self.register: list[Claim] = []
        self.total_proposed = 0
        self.killed_at: dict[int, int] = {}          # gate index -> count; 9 = veto
        self.gate_census: dict[int, dict[Grade, int]] = {
            i: {g: 0 for g in Grade} for i in range(1, 9)
        }

    # -----------------------------------------------------------------------

    def run(self, material: str) -> None:
        raw = self.agent.invoke(material + "\n\n" + PROPOSE_INSTRUCTION)
        try:
            obj = json.loads(raw)
            reading = next(r for r in Reading if r.label == obj["reading"])
            wave = WAVE_ALIASES[obj["wave"]]
            observer = Observer(**obj["observer"])
            O = Vec3.from_json(obj["O"])
            Q = Vec3.from_json(obj["Q"])
        except (json.JSONDecodeError, KeyError, StopIteration, TypeError) as e:
            log.warning("Proposal unparseable: %s", e)
            return

        self.total_proposed += 1
        axis = Axis(reading, wave, observer)
        claim_desc = json.dumps({
            "phenomenon": obj["phenomenon"],
            "reading": reading.label,
            "wave": wave,
            "observer": observer.__dict__,
        })

        chain: list[Gate] = []
        for i, rib in enumerate(RIBS, start=1):
            prior = "\n".join(
                f"  gate {g.index} (rib {g.rib}): {g.outcome.value} — {g.evidence}"
                for g in chain
            ) or "  (none)"
            prompt = GATE_INSTRUCTION.format(
                index=i, claim=claim_desc, prior=prior,
                sx=rib[0], sy=rib[1], sz=rib[2],
            )
            try:
                reply = json.loads(self.agent.invoke(prompt))
                outcome = next(g for g in Grade if g.value == reply["outcome"])
            except (json.JSONDecodeError, KeyError, StopIteration) as e:
                log.warning("Gate %d reply unparseable: %s", i, e)
                outcome = Grade.UNCONFIRMED
                reply = {"evidence": ""}

            gate = Gate(index=i, rib=rib, outcome=outcome,
                        evidence=reply.get("evidence", ""))
            chain.append(gate)
            self.gate_census[i][outcome] += 1

            if outcome is Grade.REJECTED:
                self.killed_at[i] = self.killed_at.get(i, 0) + 1
                log.info("Claim %r killed at gate %d", obj["phenomenon"], i)
                return   # claim gone; never touches register

        # Arithmetic veto (not a vote)
        computed = chord_sqnorm(O, Q)
        if computed != reading.expected:
            self.killed_at[9] = self.killed_at.get(9, 0) + 1
            log.info(
                "Claim %r vetoed by arithmetic: %s ≠ %s",
                obj["phenomenon"], computed, reading.expected,
            )
            return

        claim = Claim(
            phenomenon=obj["phenomenon"],
            chain=chain, axis=axis,
            O=O, Q=Q, computed=computed, expected=reading.expected,
        )
        self.register.append(claim)
        log.info("Claim %r survived with status %s",
                 claim.phenomenon, claim.status.value)

    # -----------------------------------------------------------------------

    def audit(self) -> dict:
        return {
            "total_proposed": self.total_proposed,
            "survived": len(self.register),
            "killed_at": {str(k): v for k, v in sorted(self.killed_at.items())},
            "gate_census": {
                str(i): {g.value: self.gate_census[i][g] for g in Grade}
                for i in range(1, 9)
            },
            "status_after_chain": {
                g.value: sum(1 for c in self.register if c.status is g)
                for g in (Grade.CONFIRMED, Grade.PLAUSIBLE, Grade.UNCONFIRMED)
            },
        }

    def to_json(self) -> str:
        return json.dumps(
            {
                "claims": [
                    {
                        "phenomenon": c.phenomenon,
                        "status": c.status.value,
                        "verified": c.verified,
                        "reading": c.axis.reading.label,
                        "wave": c.axis.wave,
                        "observer": {
                            "axis": c.axis.observer.axis,
                            "position": c.axis.observer.position,
                            "turn": c.axis.observer.turn,
                            "base60": c.axis.observer.base60,
                        },
                        "chain": [
                            {
                                "index": g.index,
                                "rib": list(g.rib),
                                "outcome": g.outcome.value,
                                "evidence": g.evidence,
                            }
                            for g in c.chain
                        ],
                        "chord": {
                            "O": [[c.O.x.a, c.O.x.b], [c.O.y.a, c.O.y.b],
                                  [c.O.z.a, c.O.z.b]],
                            "Q": [[c.Q.x.a, c.Q.x.b], [c.Q.y.a, c.Q.y.b],
                                  [c.Q.z.a, c.Q.z.b]],
                        },
                        "computed": str(c.computed),
                        "expected": str(c.expected),
                    }
                    for c in self.register
                ],
                "rule": "As above, so below. And if there is a difference, "
                        "that is friction, not error.",
            },
            indent=2,
            ensure_ascii=False,
        )


# ===========================================================================
# §8 — Callables
# ===========================================================================

def stub_call(prompt: str) -> str:
    """Deterministic stub for CI. Proposes a real rollover chord and
    passes every gate with evidence, so the chain survives cleanly."""
    if PROPOSE_INSTRUCTION in prompt:
        return json.dumps({
            "phenomenon": "Antipodal roll-over chord",
            "reading": "roll-over",
            "wave": 5,
            "observer": {"axis": 1, "position": 1, "turn": 1, "base60": 0},
            "O": [[0, 0], [1, 0], [0, 1]],
            "Q": [[-1, 0], [-1, 0], [-1, 0]],
            "ground": "fixture from test.c",
        })
    # Gate calls: confirm every rib with evidence.
    rib_line = next(
        (line for line in prompt.splitlines() if "rib (" in line), ""
    )
    return json.dumps({
        "outcome": "✓",
        "evidence": f"stub: claim crosses {rib_line.strip()}",
    })


def openai_call(prompt: str) -> str:
    import openai
    client = openai.OpenAI(api_key=os.environ["OPENAI_API_KEY"])
    resp = client.chat.completions.create(
        model=os.environ.get("ULDA_MODEL", "gpt-4o-mini"),
        messages=[{"role": "user", "content": prompt}],
        response_format={"type": "json_object"},
        temperature=0,
    )
    return resp.choices[0].message.content


def anthropic_call(prompt: str) -> str:
    import anthropic
    client = anthropic.Anthropic(api_key=os.environ["ANTHROPIC_API_KEY"])
    resp = client.messages.create(
        model=os.environ.get("ULDA_MODEL", "claude-3-5-sonnet-latest"),
        max_tokens=1024,
        messages=[{"role": "user", "content": prompt}],
    )
    return resp.content[0].text


# ===========================================================================
# §9 — Main
# ===========================================================================

def main() -> None:
    backend = os.environ.get("ULDA_BACKEND", "stub")
    call = {"stub": stub_call, "openai": openai_call,
            "anthropic": anthropic_call}[backend]
    log.info("Backend: %s", backend)

    method = Method(Agent(name="ULDA", call=call))
    method.run("Evaluate: the antipodal chord of the dodecahedron.")

    print(method.to_json())
    print("\nAudit:", json.dumps(method.audit(), indent=2, ensure_ascii=False))


if __name__ == "__main__":
    main()
