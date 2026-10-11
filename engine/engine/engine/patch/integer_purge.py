
---

---

# Engine 2 — Integer Purge Patch

**Bestand: `patch/integer_purge.py`**

```python
"""
ULDA Integer Purge Patch
========================
Drop-in vervanging voor float-gebaseerde coördinaat- en carry-berekeningen.

Vervangt:
    value = float(value) / 60.0
    carry = value // 60
    rest  = value %  60

Door:
    - vaste bit-slices (dis, ges, sar)
    - subtractie-only carries
    - 504 hardwired boundary
    - 216 macro-envelope

Geen floating-point. Geen // of %. Geen radix-drift.

License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).
"""

from __future__ import annotations
from dataclasses import dataclass

# ─────────────────────────────────────────────────────────────────────────────
# HARDWIRED CONSTANTS
# ─────────────────────────────────────────────────────────────────────────────

RADIX           = 60
MASK_CELL       = (1 << 18) - 1
SHIFT_DIS       = 0
SHIFT_GES       = 18
SHIFT_SAR       = 36
ENVELOPE_216    = 216
BOUNDARY_504    = 504
LADDER_36       = 36
PRECESSION_72   = 72
BRANCH_7        = 7


# ─────────────────────────────────────────────────────────────────────────────
# 1. DE CORE
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(slots=True)
class IntRegister:
    raw: int = 0

    @classmethod
    def encode(cls, dis: int, ges: int, sar: int) -> "IntRegister":
        return cls(
            ((dis & MASK_CELL) << SHIFT_DIS) |
            ((ges & MASK_CELL) << SHIFT_GES) |
            ((sar & MASK_CELL) << SHIFT_SAR)
        )

    def decode(self) -> tuple[int, int, int]:
        dis = (self.raw >> SHIFT_DIS) & MASK_CELL
        ges = (self.raw >> SHIFT_GES) & MASK_CELL
        sar = (self.raw >> SHIFT_SAR) & MASK_CELL
        return dis, ges, sar

    def total(self) -> int:
        dis, ges, sar = self.decode()
        return dis + ges * RADIX + sar * RADIX * RADIX


# ─────────────────────────────────────────────────────────────────────────────
# 2. DE LUM
# ─────────────────────────────────────────────────────────────────────────────

def lum_carry(reg: IntRegister, dis_in: int, ges_in: int, sar_in: int) -> IntRegister:
    dis, ges, sar = reg.decode()
    dis += dis_in
    ges += ges_in
    sar += sar_in
    while dis >= RADIX:
        dis -= RADIX
        ges += 1
    while ges >= RADIX:
        ges -= RADIX
        sar += 1
    return IntRegister.encode(dis, ges, sar)


# ─────────────────────────────────────────────────────────────────────────────
# 3. DE 504 BOUNDARY
# ─────────────────────────────────────────────────────────────────────────────

class BoundaryBreach(Exception):
    """R₂.sar > 0 → State Breached"""


def boundary_ok(reg: IntRegister, limit: int = BOUNDARY_504) -> bool:
    return reg.total() <= limit


def safe_inject(reg: IntRegister, dis_in: int, ges_in: int, sar_in: int,
                limit: int = BOUNDARY_504) -> IntRegister:
    new = lum_carry(reg, dis_in, ges_in, sar_in)
    if not boundary_ok(new, limit):
        raise BoundaryBreach(f"overflow at {new.total()}")
    return new


# ─────────────────────────────────────────────────────────────────────────────
# 4. DE 6-CIPHER
# ─────────────────────────────────────────────────────────────────────────────

SEQUENCE       = (2, 1, 3, 4, 5, 7)
OPERATORS      = tuple(SEQUENCE[i+1] - SEQUENCE[i] for i in range(len(SEQUENCE)-1))
OPERATOR_SUM   = sum(OPERATORS)
SEQUENCE_SUM   = sum(SEQUENCE)
INTERFACE_11   = 11
INTERFACE_CORR = 2 * INTERFACE_11


# ─────────────────────────────────────────────────────────────────────────────
# 5. DE CROSS-BASE OPERATOR
# ─────────────────────────────────────────────────────────────────────────────

def f_base(base: int) -> int:
    return base + BRANCH_7


F_10 = f_base(10)   # = 17
F_60 = f_base(60)   # = 67


# ─────────────────────────────────────────────────────────────────────────────
# 6. DE MACRO-ENVELOPE
# ─────────────────────────────────────────────────────────────────────────────

def envelope_216() -> int:
    base   = 5 * 2
    kernel = 3 * 2 * 5
    cage   = 8 * 9
    return (kernel * cage) // base


assert envelope_216() == ENVELOPE_216


# ─────────────────────────────────────────────────────────────────────────────
# 7. DE PATCH
# ─────────────────────────────────────────────────────────────────────────────

class IntegerPurgePatch:
    """
    Vervangt float-gebaseerde carry/coördinaat-berekeningen.
    Drop-in voor bestaande pipelines.
    """

    def __init__(self):
        self.reg = IntRegister()
        self.breaches = 0

    def inject_float(self, value: float) -> IntRegister:
        total = int(round(value * (RADIX ** 2)))
        dis = 0
        ges = 0
        sar = 0
        while total >= RADIX:
            total -= RADIX
            ges += 1
        while ges >= RADIX:
            ges -= RADIX
            sar += 1
        dis = total

        try:
            self.reg = safe_inject(self.reg, dis, ges, sar)
        except BoundaryBreach:
            self.breaches += 1
            raise
        return self.reg

    def total(self) -> int:
        return self.reg.total()

    def clean(self) -> bool:
        return boundary_ok(self.reg)


# ─────────────────────────────────────────────────────────────────────────────
# 8. ZELFTEST
# ─────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    patch = IntegerPurgePatch()

    for _ in range(503):
        patch.inject_float(1.0 / (RADIX ** 2))

    assert patch.total() == 503
    assert patch.clean() is True

    patch.inject_float(1.0 / (RADIX ** 2))
    assert patch.total() == 504
    assert patch.clean() is True

    try:
        patch.inject_float(1.0 / (RADIX ** 2))
        raise AssertionError("boundary should have tripped")
    except BoundaryBreach:
        pass

    print("ULDA Integer Purge Patch — OK")
    print("Macro-envelope:   ", envelope_216(), "= 6³")
    print("Boundary:         ", BOUNDARY_504, "= 7 × 72")
    print("Sequence:         ", SEQUENCE, " (6 omitted)")
    print("Operators:        ", OPERATORS, " sum =", OPERATOR_SUM)
    print("Interface:        ", INTERFACE_11, " correction =", INTERFACE_CORR)
    print("Cross-base f(10): ", F_10)
    print("Cross-base f(60): ", F_60)
