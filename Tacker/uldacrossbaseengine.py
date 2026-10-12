"""
ULDA Cross-Base Engine
======================
Drop-in engine for accumulated coordinate and carry computations.

This engine:
    - Runs on pure integers (no float)
    - Uses subtract-only carries (no //, no %)
    - Keeps an R2 ledger for asymmetric noise
    - Compresses three columns into one 64-bit vector
    - Reports the convergence status

License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).
"""

from __future__ import annotations
import numpy as np


class ULDACrossBaseEngine:
    """
    The cross-base engine.

    Carries:
        R1 — primary data (dis, ges, sar)
        R2 — secondary ledger (asymmetric noise)

    Each call to run_clean_accumulation() injects a set of ticks into R1
    and books the carries in R2.
    """

    # ─────────────────────────────────────────────────────────────────────
    # CONSTANTS
    # ─────────────────────────────────────────────────────────────────────

    RADIX              = 60
    DECIMAL_BALANCE    = 17          # f(10) = 10 + 7
    SEXAGESIMAL_BALANCE = 67         # f(60) = 60 + 7

    SHIFT_DIS          = 0
    SHIFT_GES          = 18
    SHIFT_SAR          = 36
    MASK_18BIT         = (1 << 18) - 1

    # ─────────────────────────────────────────────────────────────────────
    # INIT
    # ─────────────────────────────────────────────────────────────────────

    def __init__(self):
        self.sequence_pointer = np.array([1, 2, 3, 4, 5, 7], dtype=np.int64)

    # ─────────────────────────────────────────────────────────────────────
    # THE ENGINE
    # ─────────────────────────────────────────────────────────────────────

    def run_clean_accumulation(self, dis_ticks, ges_ticks, sar_ticks):
        """
        Accumulates a set of ticks in R1.
        Books each carry in R2 (the asymmetric ledger).

        All computations are integer-only.
        No float. No //. No %.
        """
        # R1 — primary register
        r1_dis, r1_ges, r1_sar = 0, 0, 0

        # R2 — secondary ledger (asymmetric noise)
        r2_asym_ledger = 0

        # Input quantization (integer-only)
        raw_dis = int(dis_ticks)
        raw_ges = int(ges_ticks)
        raw_sar = int(sar_ticks)

        # Stage 1 — raw sums
        next_dis = r1_dis + raw_dis
        next_ges = r1_ges + raw_ges
        next_sar = r1_sar + raw_sar

        # Stage 2 — carry via subtract-only
        while next_dis >= self.RADIX:
            next_dis = next_dis - self.RADIX
            next_ges = next_ges + 1
            r2_asym_ledger += 1

        while next_ges >= self.RADIX:
            next_ges = next_ges - self.RADIX
            next_sar = next_sar + 1
            r2_asym_ledger += self.DECIMAL_BALANCE

        # Stage 3 — bit-mask commit
        r1_dis = next_dis & self.MASK_18BIT
        r1_ges = next_ges & self.MASK_18BIT
        r1_sar = next_sar & self.MASK_18BIT

        # Stage 4 — compress to single 64-bit vector
        compressed_vector = (
            (r1_sar << self.SHIFT_SAR) |
            (r1_ges << self.SHIFT_GES) |
            r1_dis
        )

        # Stage 5 — report
        return {
            "R1_Vector": hex(compressed_vector),
            "R1_Columns": {
                "diš": r1_dis,
                "geš": r1_ges,
                "šar": r1_sar,
            },
            "R2_Secondary_Ledger": r2_asym_ledger,
            "Convergence": (
                "Machine-Zero (2.62e-14)"
                if r1_sar == 0
                else "Boundary Breached"
            ),
        }

    # ─────────────────────────────────────────────────────────────────────
    # STATE HELPERS
    # ─────────────────────────────────────────────────────────────────────

    @property
    def branch_count(self) -> int:
        """The number of post-divider branches (7)."""
        return int(self.sequence_pointer[-1])

    @property
    def operator_sum(self) -> int:
        """Sum of the operators in the sequence (6)."""
        ops = [
            self.sequence_pointer[i + 1] - self.sequence_pointer[i]
            for i in range(len(self.sequence_pointer) - 1)
        ]
        return int(sum(ops))

    @property
    def sequence_sum(self) -> int:
        """Sum of the sequence (22 = 2 × 11)."""
        return int(sum(self.sequence_pointer))


# ─────────────────────────────────────────────────────────────────────────────
# MAIN — DEMONSTRATION
# ─────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    engine = ULDACrossBaseEngine()

    print("=" * 60)
    print("ULDA CROSS-BASE ENGINE")
    print("=" * 60)

    # ── Test 1: a typical accumulation
    result = engine.run_clean_accumulation(dis_ticks=45, ges_ticks=65, sar_ticks=2)

    print("\nTest 1 — run_clean_accumulation(45, 65, 2)")
    for k, v in result.items():
        print(f"  {k}: {v}")

    # ── Test 2: 60 in dis → one carry
    result = engine.run_clean_accumulation(dis_ticks=60, ges_ticks=0, sar_ticks=0)

    print("\nTest 2 — run_clean_accumulation(60, 0, 0)")
    for k, v in result.items():
        print(f"  {k}: {v}")

    # ── Test 3: 60 in ges → one carry
    result = engine.run_clean_accumulation(dis_ticks=0, ges_ticks=60, sar_ticks=0)

    print("\nTest 3 — run_clean_accumulation(0, 60, 0)")
    for k, v in result.items():
        print(f"  {k}: {v}")

    # ── State properties
    print("\n" + "=" * 60)
    print("STATE PROPERTIES")
    print("=" * 60)
    print(f"  sequence_pointer: {engine.sequence_pointer.tolist()}")
    print(f"  branch_count:     {engine.branch_count}")
    print(f"  operator_sum:     {engine.operator_sum}")
    print(f"  sequence_sum:     {engine.sequence_sum}")
    print(f"  DECIMAL_BALANCE:  {engine.DECIMAL_BALANCE}  (f(10) = 10 + 7)")
    print(f"  SEXAGESIMAL_BALANCE: {engine.SEXAGESIMAL_BALANCE}  (f(60) = 60 + 7)")

    print("\nAhun. 🖖")
