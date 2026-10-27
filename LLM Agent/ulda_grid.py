#!/usr/bin/env python3
"""
ulda_grid.py — 8-rib chain, 1 arithmetic veto, integrated signal analysis,
and a reasoning log for every death.

The ℤ[φ] arithmetic is NOT reimplemented here — it's called from the C
engine via ctypes. `libulda.so` (or `.dylib`) is the single source of truth.
"""

from __future__ import annotations

import ctypes
import ctypes.util
import json
import logging
import os
import sys
from dataclasses import dataclass
from enum import Enum
from pathlib import Path
from typing import Callable

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
)
log = logging.getLogger(__name__)


# ===========================================================================
# §1 — ℤ[φ] arithmetic: called from C, not reimplemented
# ===========================================================================

@dataclass(frozen=True)
class ZPhi:
    a: int
    b: int

    def __add__(self, o): return ZPhi(self.a + o.a, self.b + o.b)
    def __sub__(self, o): return ZPhi(self.a - o.a, self.b - o.b)
    def __eq__(self, o):
        return isinstance(o, ZPhi) and (self.a, self.b) == (o.a, o.b)
    def __str__(self): return f"{self.a} + {self.b}φ"


@dataclass(frozen=True)
class Vec3:
    x: ZPhi
    y: ZPhi
    z: ZPhi

    @staticmethod
    def from_json(arr):
        return Vec3(ZPhi(*arr[0]), ZPhi(*arr[1]), ZPhi(*arr[2]))

    def to_json(self):
        return [[self.x.a, self.x.b],
                [self.y.a, self.y.b],
                [self.z.a, self.z.b]]


# ---- ctypes shim to the C engine ----------------------------------------

def _load_libulda() -> ctypes.CDLL:
    """Load libulda.so/.dylib from the script's directory, then sys.path."""
    here = Path(__file__).resolve().parent
    candidates = [
        here / "libulda.dylib",
        here / "libulda.so",
        Path("libulda.dylib"),
        Path("libulda.so"),
    ]
    for path in candidates:
        if path.exists():
            log.info("Loaded engine: %s", path)
            return ctypes.CDLL(str(path))
    found = ctypes.util.find_library("ulda")
    if found:
        log.info("Loaded engine from system: %s", found)
        return ctypes.CDLL(found)
    raise RuntimeError(
        "libulda not found. Run `make lib` first. "
        "Looked for libulda.so / libulda.dylib."
    )


_lib = _load_libulda()
_lib.chord_sqnorm_flat.argtypes = (
    [ctypes.c_longlong] * 12
    + [ctypes.POINTER(ctypes.c_longlong),
       ctypes.POINTER(ctypes.c_longlong)]
)
_lib.chord_sqnorm_flat.restype = None


def chord_sqnorm(O: Vec3, Q: Vec3) -> ZPhi:
    """Call the C engine: chord_sqnorm(O, Q) in ℤ[φ]³."""
    out_a = ctypes.c_longlong()
    out_b = ctypes.c_longlong()
    _lib.chord_sqnorm_flat(
        O.x.a, O.x.b, O.y.a, O.y.b, O.z.a, O.z.b,
        Q.x.a, Q.x.b, Q.y.a, Q.y.b, Q.z.a, Q.z.b,
        ctypes.byref(out_a), ctypes.byref(out_b),
    )
    return ZPhi(out_a.value, out_b.value)


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
# §3 — Readings, observer
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
# §4 — 8 ribs
# ===========================================================================

RIBS = [
    (1, 1, 1), (1, 1, -1), (1, -1, 1), (1, -1, -1),
    (-1, 1, 1), (-1, 1, -1), (-1, -1, 1), (-1, -1, -1),
]


# ===========================================================================
# §5 — Gates, claims, deaths
# ===========================================================================

@dataclass
class Gate:
    index: int
    rib: tuple[int, int, int]
    outcome: Grade
    evidence: str = ""

    def __post_init__(self):
        if self.outcome in (Grade.CONFIRMED, Grade.REJECTED) and not self.evidence:
            raise ValueError(
                f"gate {self.index}: {self.outcome.value} requires evidence"
            )

    def line(self) -> str:
        return f"Gate {self.index} (rib {self.rib}): {self.outcome.value} — {self.evidence}"


@dataclass
class DeathReasoning:
    phenomenon: str
    died_at: int
    cause: str
    reasoning: list[str]
    conclusion: str

    def _assert_valid(self) -> None:
        assert self.reasoning, "reasoning must not be empty"
        for line in self.reasoning[:-1]:
            assert "✗" not in line, (
                f"✗ appeared before killing gate in {self.phenomenon!r}: {line}"
            )
        last = self.reasoning[-1]
        if self.cause == "rib_rejection":
            assert last.startswith(f"Gate {self.died_at}") and "✗" in last, (
                f"last reasoning line is not the killing gate: {last!r}"
            )
        elif self.cause == "arithmetic_veto":
            assert last.startswith("Veto:"), (
                f"last reasoning line is not a veto: {last!r}"
            )
        else:
            raise AssertionError(f"unknown cause: {self.cause}")


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

    @property
    def heeft_frictie(self) -> bool:
        return any(g.outcome is Grade.PLAUSIBLE for g in self.chain)

    @property
    def aantal_frictie(self) -> int:
        return sum(1 for g in self.chain if g.outcome is Grade.PLAUSIBLE)

    @property
    def heeft_onzekerheid(self) -> bool:
        return any(g.outcome is Grade.UNCONFIRMED for g in self.chain)

    @property
    def aantal_onzekerheid(self) -> int:
        return sum(1 for g in self.chain if g.outcome is Grade.UNCONFIRMED)

    @property
    def gates_doorlopen(self) -> int:
        return len(self.chain)

    def _assert_consistent(self) -> None:
        assert self.status == min((g.outcome for g in self.chain), key=_ORDER.get)
        if self.status is Grade.CONFIRMED:
            assert not self.heeft_frictie and not self.heeft_onzekerheid
        elif self.status is Grade.PLAUSIBLE:
            assert self.heeft_frictie and not self.heeft_onzekerheid
        elif self.status is Grade.UNCONFIRMED:
            assert self.heeft_onzekerheid
        assert self.verified


# ===========================================================================
# §6 — Agent
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
  "O": [[a,b],[a,b],[a,b]],
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
  {{"outcome": "✓"|"~"|"?"|"✗", "evidence": "..."}}

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
        self.killed_claims: list[DeathReasoning] = []
        self.total_proposed = 0
        self.killed_at: dict[int, int] = {}
        self.gate_census: dict[int, dict[Grade, int]] = {
            i: {g: 0 for g in Grade} for i in range(1, 9)
        }

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

        log.info("Proposed: %s", json.dumps({
            **json.loads(claim_desc),
            "O": O.to_json(),
            "Q": Q.to_json(),
        }))

        chain: list[Gate] = []
        for i, rib in enumerate(RIBS, start=1):
            prior = "\n".join(g.line() for g in chain) or "  (none)"
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
                self._record_rib_rejection(obj["phenomenon"], chain, gate)
                return

        # ---- arithmetic veto: called from C via ctypes ----
        computed = chord_sqnorm(O, Q)
        if computed != reading.expected:
            self._record_arithmetic_veto(
                obj["phenomenon"], chain, reading, computed,
            )
            return

        claim = Claim(
            phenomenon=obj["phenomenon"],
            chain=chain, axis=axis,
            O=O, Q=Q, computed=computed, expected=reading.expected,
        )
        claim._assert_consistent()
        self.register.append(claim)
        log.info("Claim %r survived with status %s",
                 claim.phenomenon, claim.status.value)

    def _record_rib_rejection(self, phenomenon: str,
                              chain: list[Gate], killing: Gate) -> None:
        reasoning = [g.line() for g in chain]
        conclusion = (
            f"The claim is severed at gate {killing.index}. "
            f"The chain established {len(chain) - 1} premise(s) before the "
            f"contradiction: "
            + " ".join(f"gate {g.index} said {g.outcome.value}." for g in chain[:-1])
            + f" Gate {killing.index} then returned ✗ with irrefutable "
            f"evidence — namely: {killing.evidence}. "
            f"All 8 gates must pass for a claim to survive; a single ✗ "
            f"cannot be compensated by later gates, and the short-circuit "
            f"means gates {killing.index + 1}..8 were never asked. "
            f"The claim is dead."
        )
        death = DeathReasoning(
            phenomenon=phenomenon,
            died_at=killing.index,
            cause="rib_rejection",
            reasoning=reasoning,
            conclusion=conclusion,
        )
        death._assert_valid()
        self.killed_claims.append(death)
        self.killed_at[killing.index] = self.killed_at.get(killing.index, 0) + 1
        log.info("Claim %r killed at gate %d: %s",
                 phenomenon, killing.index, killing.evidence)

    def _record_arithmetic_veto(self, phenomenon: str,
                                chain: list[Gate],
                                reading: Reading, computed: ZPhi) -> None:
        reasoning = [g.line() for g in chain]
        reasoning.append(
            f"Veto: chord_sqnorm(Q − O) = {computed}, but reading "
            f"{reading.label} requires {reading.expected}. "
            f"Difference: {computed - reading.expected}."
        )
        conclusion = (
            f"The claim passed all 8 rib gates. "
            f"The arithmetic veto then rejected it: the chord's squared "
            f"norm is {computed}, but the reading '{reading.label}' "
            f"requires {reading.expected}. The rib gates confirmed the "
            f"geometry was consistent with the claim; the veto confirms "
            f"the claim's invariant is wrong. The veto is decisive — a "
            f"claim whose invariant is wrong cannot enter the register, "
            f"regardless of how many gates it passed."
        )
        death = DeathReasoning(
            phenomenon=phenomenon,
            died_at=9,
            cause="arithmetic_veto",
            reasoning=reasoning,
            conclusion=conclusion,
        )
        death._assert_valid()
        self.killed_claims.append(death)
        self.killed_at[9] = self.killed_at.get(9, 0) + 1
        log.info("Claim %r vetoed: %s ≠ %s (diff %s)",
                 phenomenon, computed, reading.expected,
                 computed - reading.expected)

    def _assert_kill_consistency(self) -> None:
        counts: dict[int, int] = {}
        for k in self.killed_claims:
            counts[k.died_at] = counts.get(k.died_at, 0) + 1
        assert counts == self.killed_at, (
            f"killed_at {self.killed_at} disagrees with killed_claims {counts}"
        )

    def audit(self) -> dict:
        self._assert_kill_consistency()
        return {
            "total_proposed": self.total_proposed,
            "survived": len(self.register),
            "killed_at": {str(k): v for k, v in sorted(self.killed_at.items())},
            "killed_claims": [
                {
                    "phenomenon": k.phenomenon,
                    "died_at": k.died_at,
                    "cause": k.cause,
                    "reasoning": k.reasoning,
                    "conclusion": k.conclusion,
                }
                for k in self.killed_claims
            ],
            "gate_census": {
                str(i): {g.value: self.gate_census[i][g] for g in Grade}
                for i in range(1, 9)
            },
            "status_after_chain": {
                g.value: sum(1 for c in self.register if c.status is g)
                for g in (Grade.CONFIRMED, Grade.PLAUSIBLE, Grade.UNCONFIRMED)
            },
            "claims_with_frictie": sum(1 for c in self.register if c.heeft_frictie),
            "claims_with_onzekerheid": sum(1 for c in self.register if c.heeft_onzekerheid),
            "total_frictie_gates": sum(c.aantal_frictie for c in self.register),
            "total_onzekerheid_gates": sum(c.aantal_onzekerheid for c in self.register),
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
                        "wave": str(c.axis.wave),
                        "signaal_analyse": {
                            "heeft_frictie (~/Plausible)": c.heeft_frictie,
                            "aantal_frictie": c.aantal_frictie,
                            "heeft_onzekerheid (?/Unconfirmed)": c.heeft_onzekerheid,
                            "aantal_onzekerheid": c.aantal_onzekerheid,
                            "gates_doorlopen": c.gates_doorlopen,
                            "gates_verwacht": len(RIBS),
                        },
                        "matrix_inspectie": [
                            {
                                "gate": g.index,
                                "rib": list(g.rib),
                                "outcome": g.outcome.value,
                                "evidence": g.evidence
                                    if g.evidence
                                    else "(geen hardware-bewijs geleverd)",
                            }
                            for g in c.chain
                        ],
                        "chord": {
                            "O": c.O.to_json(),
                            "Q": c.Q.to_json(),
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
