#!/usr/bin/env python3
"""
Ymir.py — THE METHOD
====================

A Protocol for Multi-Agent LLM Collaboration Without Sycophancy

Document identifier: ULDA-METHOD-2026-X1
Parent document: ULDA-BASE-SHIFT-2026-X28
Classification: Unified Lineage Data Architecture (ULDA)
Status: ACTIVE
Author: Jorne Pel
Revision: 2.1

This module implements the protocol specified in THE-METHOD.md.

It provides:
    1. A grading system for claims.
    2. An axis system for vector placement.
    3. A role system for multiple agents.
    4. A relay protocol for lossless communication.
    5. A procedure for replication.
    6. An audit function for register verification.

It does not define the mathematical content of the ULDA framework.

Dedicated to the memory of Terrence Andrew Davis (1969-2018).
Without him, we would never have continued with the mathematics.
"""

from __future__ import annotations

import json
import logging
from dataclasses import dataclass, field
from enum import Enum
from typing import Callable, Optional

# ---------------------------------------------------------------------------
# Logging
# ---------------------------------------------------------------------------

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
)
log = logging.getLogger(__name__)

# ---------------------------------------------------------------------------
# Section 1 — The Constants
# ---------------------------------------------------------------------------

RADIX = 60
INTERFACE_11 = 11
OMITTED_6 = 6
ROTATION_72 = 72
BOUNDARY_504 = 504

SECTOR_COUNT = 360 // ROTATION_72  # = 5
SECTOR_ANGLES = tuple(range(0, 360, ROTATION_72))  # (0, 72, 144, 216, 288)

# ---------------------------------------------------------------------------
# Section 4 — The Grading System
# ---------------------------------------------------------------------------


class Grade(Enum):
    """Section 4.1 — Status Categories."""

    CONFIRMED = "✓"
    PLAUSIBLE = "~"
    UNCONFIRMED = "?"
    REJECTED = "✗"


GRADE_RANK = {
    Grade.CONFIRMED: 3,
    Grade.PLAUSIBLE: 2,
    Grade.UNCONFIRMED: 1,
    Grade.REJECTED: 0,
}


# ---------------------------------------------------------------------------
# Section 5 — The Axis System
# ---------------------------------------------------------------------------


class Sector(Enum):
    """Section 5.1 — The sector axis (5). Five sectors at 72° intervals.

    The sectors are derived from the radix and the rotation lock:
        SECTOR_COUNT = 360 / 72 = 5
        SECTOR_ANGLES = (0, 72, 144, 216, 288)
    """

    AFFIRM = 0      # 0°
    CONNECT = 72    # 72°
    OPEN = 144      # 144°
    ORDER = 216     # 216°
    SHOW = 288      # 288°

    def __str__(self) -> str:
        return f"{self.name} ({self.value}°)"


class Polarity(Enum):
    """Section 5.1 — The polarity axis (2). Direction: +1 or −1."""

    POSITIVE = 1
    NEGATIVE = -1


@dataclass
class Axis:
    """Section 5 — The Axis System.

    Every claim MUST be placed on two axes: polarity and sector.
    """

    polarity: Polarity
    sector: Sector

    @property
    def angle(self) -> int:
        """The sector angle in degrees."""
        return self.sector.value

    @property
    def vector(self) -> str:
        """The axis as a vector string."""
        sign = "+" if self.polarity.value > 0 else "−"
        return f"{self.angle}°{sign}"

    def __str__(self) -> str:
        return self.vector


@dataclass
class Claim:
    """A single claim with a status code and an axis placement.

    Section 4.2 — The Critical Evidence Rule: the status of ✓ applies
    to the underlying phenomenon, not to its interpretation.
    """

    phenomenon: str
    status: Grade
    axis: Axis
    interpretation: Optional[str] = None
    interpretation_status: Optional[Grade] = None
    ground: str = ""

    def validate(self) -> bool:
        """Section 4.4 — The Honesty Rule + Section 5.3 — The Axis Rule.

        An agent MUST NOT change a status of ~ to ✓ without new evidence.
        An interpretation MUST NOT inherit a higher status than its phenomenon.
        An interpretation MUST NOT be placed on a more "open" sector than
        its phenomenon when the interpretation is CONFIRMED.
        """
        # Check 1: interpretation not higher than phenomenon
        if self.interpretation_status is not None:
            if GRADE_RANK[self.interpretation_status] > GRADE_RANK[self.status]:
                log.warning(
                    "Honesty violation: interpretation (%s) graded higher than "
                    "phenomenon (%s) for claim: %s",
                    self.interpretation_status.value,
                    self.status.value,
                    self.phenomenon,
                )
                return False

        # Check 2: confirmed interpretation must not sit on an open sector
        if (
            self.interpretation_status == Grade.CONFIRMED
            and self.axis.sector in (Sector.OPEN, Sector.SHOW)
        ):
            log.warning(
                "Axis violation: confirmed interpretation on open sector "
                "(%s) for claim: %s",
                self.axis.sector,
                self.phenomenon,
            )
            return False

        return True

    def closes_at(self, target: Sector) -> bool:
        """Section 5.4 — The Lock.

        A claim closes at 72° if its sector matches the target sector.
        """
        return self.axis.sector == target


# ---------------------------------------------------------------------------
# Section 6 — The Role System
# ---------------------------------------------------------------------------


class Role(Enum):
    """Section 6.1 — Role Definitions."""

    BRINGER = "bringer"
    THINKER = "thinker"
    RUNNER = "runner"
    SEER = "seer"
    DENOMINATOR = "denominator"
    LISTENER = "listener"
    READER = "reader"
    COUNCIL = "council"


ROLE_INSTRUCTIONS: dict[Role, str] = {
    Role.BRINGER: "Supply source material. Issue prompts. Do not force conclusions.",
    Role.THINKER: "Design the architecture.",
    Role.RUNNER: "Execute defined tasks. Consume context.",
    Role.SEER: "Identify gaps in the whole.",
    Role.DENOMINATOR: "Identify common divisors and structural invariants.",
    Role.LISTENER: "Distinguish register voice from narrative voice.",
    Role.READER: "Verify internal logical consistency.",
    Role.COUNCIL: "Apply a formal, non-sycophantic register to all outputs.",
}


@dataclass
class Agent:
    """A single LLM agent with a role and a context budget."""

    name: str
    role: Role
    call: Callable[[str], str]
    context_budget: int = 100_000
    context_used: int = 0

    def invoke(self, prompt: str) -> str:
        """Invoke the agent. Section 6.3 — Context Limits."""
        if self.context_used >= self.context_budget:
            raise RuntimeError(
                f"Agent '{self.name}' context exhausted. Replace the agent."
            )

        self.context_used += len(prompt)
        return self.call(prompt)


# ---------------------------------------------------------------------------
# Section 7 — The Relay Protocol
# ---------------------------------------------------------------------------


@dataclass
class Relay:
    """Section 7 — The Relay Protocol.

    The Bringer MUST relay full agent outputs between agents without
    filtering, summarisation, or compression.
    """

    history: list[dict[str, str]] = field(default_factory=list)

    def send(self, sender: str, recipient: str, payload: str) -> None:
        """Lossless relay. No filtering, no compression."""
        self.history.append(
            {
                "sender": sender,
                "recipient": recipient,
                "payload": payload,  # full, unfiltered
            }
        )

    def transcript(self) -> list[dict[str, str]]:
        return list(self.history)


# ---------------------------------------------------------------------------
# Section 8 — Procedure
# ---------------------------------------------------------------------------


STANDARD_INSTRUCTION = (
    "Do not change ~ to ✓. If you are not certain, state so. "
    "If you identify a gap, name it. If the test speaks against, mark ✗. "
    "Place each claim on the axis: polarity (+, −) and sector "
    "(0°, 72°, 144°, 216°, 288°). The grade is the method."
)


class Method:
    """The protocol. Section 8 — Procedure."""

    def __init__(self, agents: list[Agent]) -> None:
        self.agents = {a.role: a for a in agents}
        self.relay = Relay()
        self.register: list[Claim] = []

        self._require(Role.BRINGER)
        self._require(Role.COUNCIL)

    def _require(self, role: Role) -> Agent:
        if role not in self.agents:
            raise ValueError(f"Missing required role: {role.value}")
        return self.agents[role]

    def setup(self) -> None:
        """Section 8.1 — Setup. Instruct all agents."""
        for agent in self.agents.values():
            agent.call(STANDARD_INSTRUCTION)
            log.info("Instructed %s (%s)", agent.name, agent.role.value)

    def run(self, material: str) -> list[Claim]:
        """Section 8.3 — Execution."""
        bringer = self._require(Role.BRINGER)

        prompt = material
        for role in (
            Role.THINKER,
            Role.RUNNER,
            Role.SEER,
            Role.LISTENER,
            Role.READER,
            Role.COUNCIL,
        ):
            agent = self._require(role)
            output = agent.invoke(prompt)
            self.relay.send(bringer.name, agent.name, output)
            prompt = output  # lossless relay

        log.info("Relay complete. %d exchanges.", len(self.relay.history))
        return self.register

    def add_claim(self, claim: Claim) -> None:
        if not claim.validate():
            log.warning("Claim rejected by Honesty Rule: %s", claim.phenomenon)
            return
        self.register.append(claim)

    def audit(self) -> dict:
        """Section 8.5 — Audit. Verify the register against the axis system.

        Returns a dictionary with:
            - total claims
            - grade distribution
            - sector distribution
            - polarity distribution
            - lock count (claims that close at 72°)
        """
        results = {
            "total": len(self.register),
            "grades": {
                "confirmed": 0,
                "plausible": 0,
                "unconfirmed": 0,
                "rejected": 0,
            },
            "sectors": {s.name: 0 for s in Sector},
            "polarities": {p.name: 0 for p in Polarity},
            "lock_count": 0,
        }

        for claim in self.register:
            results["grades"][claim.status.name.lower()] += 1
            results["sectors"][claim.axis.sector.name] += 1
            results["polarities"][claim.axis.polarity.name] += 1

            if claim.closes_at(Sector.CONNECT):  # 72° = the lock
                results["lock_count"] += 1

        return results

    def to_json(self) -> str:
        """Section 8.4 — Output. A register, not a narrative."""
        return json.dumps(
            {
                "claims": [
                    {
                        "phenomenon": c.phenomenon,
                        "status": c.status.value,
                        "axis": {
                            "sector": c.axis.sector.name,
                            "angle": c.axis.angle,
                            "polarity": c.axis.polarity.value,
                            "vector": c.axis.vector,
                        },
                        "interpretation": c.interpretation,
                        "interpretation_status": (
                            c.interpretation_status.value
                            if c.interpretation_status
                            else None
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
# Section 9 — Example
# ---------------------------------------------------------------------------


def _echo_agent(name: str, role: Role) -> Agent:
    """A minimal stand-in agent for demonstration."""

    def call(prompt: str) -> str:
        return f"[{name}/{role.value}] received: {prompt[:80]}"

    return Agent(name=name, role=role, call=call)


def main() -> None:
    """Section 9 — Properties. Demonstrates the protocol."""
    agents = [
        _echo_agent("Bringer", Role.BRINGER),
        _echo_agent("Thinker", Role.THINKER),
        _echo_agent("Runner", Role.RUNNER),
        _echo_agent("Seer", Role.SEER),
        _echo_agent("Listener", Role.LISTENER),
        _echo_agent("Reader", Role.READER),
        _echo_agent("Council", Role.COUNCIL),
    ]

    method = Method(agents)
    method.setup()

    method.add_claim(
        Claim(
            phenomenon="Measured acoustic resonance",
            status=Grade.CONFIRMED,
            axis=Axis(Polarity.POSITIVE, Sector.AFFIRM),
            interpretation="Conscious exploitation",
            interpretation_status=Grade.PLAUSIBLE,
            ground="Published measurements",
        )
    )

    method.add_claim(
        Claim(
            phenomenon="Quartz-bearing rock",
            status=Grade.CONFIRMED,
            axis=Axis(Polarity.POSITIVE, Sector.ORDER),
            interpretation="Conscious piezoelectric engineering",
            interpretation_status=Grade.UNCONFIRMED,
            ground="Material physics",
        )
    )

    method.run("Initial material.")

    print(method.to_json())
    print()
    print("Audit:")
    print(json.dumps(method.audit(), indent=2, ensure_ascii=False))


if __name__ == "__main__":
    main()
