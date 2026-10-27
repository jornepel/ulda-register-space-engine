#!/usr/bin/env python3
"""
ulda_agent.py — Single-agent ULDA protocol (new axis system).

The axis system is the four readings of §8 (ℤ[φ] engine) crossed with the
wave modes of §7. Every claim carries an observer label (axis, position,
turn, base60) and is graded by the Honesty Rule. One agent, one register.
"""

from __future__ import annotations

import json
import logging
import os
from dataclasses import dataclass, field
from enum import Enum
from typing import Callable, Optional

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
)
log = logging.getLogger(__name__)


# ---------------------------------------------------------------------------
# Axis system — Reading × Wave (replaces Sector × Polarity)
# ---------------------------------------------------------------------------

class Reading(Enum):
    """§8 — the four invariants of the ℤ[φ] engine."""
    ROLLOVER = ("roll-over",  "7 + 3φ", "METRIC")
    MIRROR   = ("mirror",     "3 + φ",  "METRIC")
    LOOP     = ("loop",       "5",      "STRUCTURAL")
    OFFSET   = ("offset",     "1",      "STRUCTURAL")

    def __init__(self, label: str, expected: str, kind: str):
        self.label = label
        self.expected = expected
        self.kind = kind


class Wave(Enum):
    """§7 — wave modes. WAVE_3P (3') is distinct from WAVE_3 (3)."""
    UNASSIGNED = 0
    W1 = 1
    W3 = 3
    W3P = "3'"
    W4 = 4
    W5 = 5

    def __str__(self) -> str:
        return "—" if self is Wave.UNASSIGNED else str(self.value)


@dataclass(frozen=True)
class Observer:
    """Base-60 observer label, matching `label` in ulda.h."""
    axis: int          # 1..6
    position: int      # +1 or -1
    turn: int          # 1 or 2
    base60: int        # 0, 12, 24, 36, 48

    def __post_init__(self):
        if not (1 <= self.axis <= 6):
            raise ValueError(f"axis out of range: {self.axis}")
        if self.position not in (-1, 1):
            raise ValueError(f"position must be ±1: {self.position}")
        if self.turn not in (1, 2):
            raise ValueError(f"turn must be 1 or 2: {self.turn}")
        if self.base60 not in (0, 12, 24, 36, 48):
            raise ValueError(f"base60 must be one of 0,12,24,36,48: {self.base60}")

    def __str__(self) -> str:
        sign = "+" if self.position > 0 else "−"
        return f"{self.axis}{sign}/t{self.turn}/b{self.base60}"


@dataclass
class Axis:
    """Every claim sits on (reading, wave, observer)."""
    reading: Reading
    wave: Wave
    observer: Observer

    def __str__(self) -> str:
        return f"{self.reading.label}/{self.wave}/{self.observer}"


# ---------------------------------------------------------------------------
# Grading
# ---------------------------------------------------------------------------

class Grade(Enum):
    CONFIRMED   = "✓"
    PLAUSIBLE   = "~"
    UNCONFIRMED = "?"
    REJECTED    = "✗"


GRADE_RANK = {g: i for i, g in enumerate(
    [Grade.REJECTED, Grade.UNCONFIRMED, Grade.PLAUSIBLE, Grade.CONFIRMED]
)}


@dataclass
class Claim:
    phenomenon: str
    status: Grade
    axis: Axis
    interpretation: Optional[str] = None
    interpretation_status: Optional[Grade] = None
    interpretation_axis: Optional[Axis] = None
    ground: str = ""

    def validate(self) -> bool:
        """§4.4 Honesty Rule + §5.3 Axis Rule."""
        if self.interpretation_status is not None:
            if GRADE_RANK[self.interpretation_status] > GRADE_RANK[self.status]:
                log.warning(
                    "Honesty violation: interpretation (%s) > phenomenon (%s): %s",
                    self.interpretation_status.value, self.status.value,
                    self.phenomenon,
                )
                return False

        if (
            self.interpretation_status == Grade.CONFIRMED
            and self.interpretation_axis is not None
            and self.interpretation_axis.reading in (Reading.ROLLOVER, Reading.LOOP)
        ):
            log.warning(
                "Axis violation: confirmed interpretation on open reading "
                "(%s): %s",
                self.interpretation_axis.reading.label, self.phenomenon,
            )
            return False

        return True

    def closes_at(self, reading: Reading) -> bool:
        """§5.4 Lock — a claim closes when its reading matches."""
        return self.axis.reading == reading


# ---------------------------------------------------------------------------
# The single agent
# ---------------------------------------------------------------------------

@dataclass
class Agent:
    """One LLM (or stub) with a role, a callable, and a context budget."""
    name: str
    call: Callable[[str], str]
    context_budget: int = 100_000
    context_used: int = 0

    def invoke(self, prompt: str) -> str:
        if self.context_used >= self.context_budget:
            raise RuntimeError(f"Agent '{self.name}' context exhausted.")
        self.context_used += len(prompt)
        return self.call(prompt)


# ---------------------------------------------------------------------------
# The protocol
# ---------------------------------------------------------------------------

STANDARD_INSTRUCTION = """\
You are the ULDA agent. Your job is to grade claims and place them on axes.

Rules:
  - Do not change ~ to ✓ without new evidence.
  - An interpretation MUST NOT be graded higher than its phenomenon.
  - Place each claim on three coordinates:
      reading ∈ {roll-over, mirror, loop, offset}
      wave    ∈ {1, 3, 3', 4, 5}
      observer = (axis 1..6, position ±1, turn 1 or 2, base60 ∈ {0,12,24,36,48})
  - Expected invariant per reading (the engine will verify):
      roll-over → 7 + 3φ
      mirror    → 3 + φ
      loop      → 5
      offset    → 1
  - If you cannot verify, say so and mark ~ or ?. If it fails, mark ✗.

Reply with a single JSON object:
  {"phenomenon": str,
   "status": "✓"|"~"|"?"|"✗",
   "reading": "roll-over"|"mirror"|"loop"|"offset",
   "wave": 1|3|"3'"|4|5,
   "observer": {"axis": int, "position": int, "turn": int, "base60": int},
   "interpretation": str|null,
   "interpretation_status": "✓"|"~"|"?"|"✗"|null,
   "interpretation_reading": "roll-over"|"mirror"|"loop"|"offset"|null,
   "ground": str}
"""


class Method:
    """The protocol. One agent, one register."""

    def __init__(self, agent: Agent) -> None:
        self.agent = agent
        self.register: list[Claim] = []

    def setup(self) -> None:
        self.agent.call(STANDARD_INSTRUCTION)
        log.info("Instructed %s", self.agent.name)

    def run(self, material: str) -> list[Claim]:
        """Ask the agent to propose a claim for `material`, parse, validate."""
        raw = self.agent.invoke(material)
        claim = self._parse_claim(raw)
        if claim is not None and claim.validate():
            self.register.append(claim)
            log.info("Accepted: %s", claim.phenomenon)
        return self.register

    @staticmethod
    def _parse_claim(raw: str) -> Optional[Claim]:
        try:
            obj = json.loads(raw)
            reading = next(r for r in Reading if r.label == obj["reading"])
            wave = next(
                w for w in Wave
                if str(w.value) == str(obj["wave"]) or w.value == obj["wave"]
            )
            observer = Observer(**obj["observer"])
            axis = Axis(reading, wave, observer)

            interp_axis = None
            if obj.get("interpretation_reading"):
                r = next(
                    rr for rr in Reading
                    if rr.label == obj["interpretation_reading"]
                )
                interp_axis = Axis(r, wave, observer)

            return Claim(
                phenomenon=obj["phenomenon"],
                status=next(g for g in Grade if g.value == obj["status"]),
                axis=axis,
                interpretation=obj.get("interpretation"),
                interpretation_status=(
                    next(g for g in Grade
                         if g.value == obj["interpretation_status"])
                    if obj.get("interpretation_status") else None
                ),
                interpretation_axis=interp_axis,
                ground=obj.get("ground", ""),
            )
        except (json.JSONDecodeError, KeyError, StopIteration, TypeError) as e:
            log.warning("Agent reply not parseable: %s", e)
            return None

    def audit(self) -> dict:
        """Per-reading, per-wave, per-grade distribution + lock count."""
        return {
            "total": len(self.register),
            "grades": {g.name.lower(): 0 for g in Grade},
            "readings": {r.label: 0 for r in Reading},
            "waves": {str(w): 0 for w in Wave},
            "lock_count": sum(
                1 for c in self.register if c.closes_at(Reading.MIRROR)
            ),
        }

    def to_json(self) -> str:
        return json.dumps(
            {
                "claims": [
                    {
                        "phenomenon": c.phenomenon,
                        "status": c.status.value,
                        "axis": {
                            "reading": c.axis.reading.label,
                            "expected": c.axis.reading.expected,
                            "wave": str(c.axis.wave),
                            "observer": {
                                "axis": c.axis.observer.axis,
                                "position": c.axis.observer.position,
                                "turn": c.axis.observer.turn,
                                "base60": c.axis.observer.base60,
                            },
                        },
                        "interpretation": c.interpretation,
                        "interpretation_status": (
                            c.interpretation_status.value
                            if c.interpretation_status else None
                        ),
                        "ground": c.ground,
                    }
                    for c in self.register
                ],
                "rule": "As above, so below. And if there is a difference, "
                        "that is friction, not error.",
            },
            indent=2,
            ensure_ascii=False,
        )


# ---------------------------------------------------------------------------
# Callables — stub, fixture, or real LLM
# ---------------------------------------------------------------------------

def stub_call(prompt: str) -> str:
    """Canned reply, useful for CI. Returns a valid claim."""
    return json.dumps({
        "phenomenon": "Stub material",
        "status": "~",
        "reading": "mirror",
        "wave": 3,
        "observer": {"axis": 3, "position": 1, "turn": 1, "base60": 12},
        "interpretation": None,
        "interpretation_status": None,
        "interpretation_reading": None,
        "ground": "stub",
    })


def openai_call(prompt: str) -> str:
    """Real LLM call. Requires OPENAI_API_KEY in the environment."""
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
    """Real LLM call. Requires ANTHROPIC_API_KEY."""
    import anthropic
    client = anthropic.Anthropic(api_key=os.environ["ANTHROPIC_API_KEY"])
    resp = client.messages.create(
        model=os.environ.get("ULDA_MODEL", "claude-3-5-sonnet-latest"),
        max_tokens=1024,
        messages=[{"role": "user", "content": prompt}],
    )
    return resp.content[0].text


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> None:
    backend = os.environ.get("ULDA_BACKEND", "stub")
    call = {"stub": stub_call, "openai": openai_call,
            "anthropic": anthropic_call}[backend]
    log.info("Using backend: %s", backend)

    agent = Agent(name="ULDA", call=call)
    method = Method(agent)
    method.setup()
    method.run("Evaluate: quartz-bearing rock with measured acoustic resonance.")

    print(method.to_json())
    print("\nAudit:", json.dumps(method.audit(), indent=2))


if __name__ == "__main__":
    main()
