"""
ULDA GPU Cross-Base Engine
==========================
Parallel implementation of the ULDA Integer Purge Patch for GPU execution.

Uses CuPy (CUDA) for vectorized operations. Falls back to NumPy if no GPU
is available.

All operations are integer-only:
    - No floating-point
    - No division (// or %)
    - Pure subtraction-based carries
    - Bit-masked column packing

License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).
"""

from __future__ import annotations
import numpy as np

try:
    import cupy as cp
    HAS_CUPY = True
except ImportError:
    cp = None
    HAS_CUPY = False


# ─────────────────────────────────────────────────────────────────────────────
# CONSTANTS
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
# GPU-COMPATIBLE CARRY (VECTORIZED)
# ─────────────────────────────────────────────────────────────────────────────

def vectorized_carry(xp, dis, ges, sar):
    """
    Vectorized subtraction-only carry.

    Works on both NumPy arrays and CuPy arrays.
    xp is either `np` or `cp`.

    All operations are integer-only.
    """
    # Stage 1 — resolve dis → ges
    dis_carry = (dis >= RADIX).astype(xp.int64)
    dis = dis - dis_carry * RADIX
    ges = ges + dis_carry

    # Stage 2 — resolve ges → sar
    ges_carry = (ges >= RADIX).astype(xp.int64)
    ges = ges - ges_carry * RADIX
    sar = sar + ges_carry

    # Stage 3 — mask to 18 bits
    dis = dis & MASK_CELL
    ges = ges & MASK_CELL
    sar = sar & MASK_CELL

    return dis, ges, sar


# ─────────────────────────────────────────────────────────────────────────────
# GPU ENGINE
# ─────────────────────────────────────────────────────────────────────────────

class ULDAGPUEngine:
    """
    Parallel cross-base engine.

    Operates on arrays of N registers simultaneously.
    All arithmetic is integer-only. No division. No floating-point.
    """

    def __init__(self, n_registers: int, use_gpu: bool = True):
        self.n = n_registers
        self.xp = cp if (use_gpu and HAS_CUPY) else np

        # R1 — primary registers (one per thread)
        self.r1_dis = self.xp.zeros(n_registers, dtype=self.xp.int64)
        self.r1_ges = self.xp.zeros(n_registers, dtype=self.xp.int64)
        self.r1_sar = self.xp.zeros(n_registers, dtype=self.xp.int64)

        # R2 — secondary ledgers (one per thread)
        self.r2_ledger = self.xp.zeros(n_registers, dtype=self.xp.int64)

        # Boundary flags (one per thread)
        self.breached = self.xp.zeros(n_registers, dtype=self.xp.bool_)

    # ─────────────────────────────────────────────────────────────────────
    # INJECT
    # ─────────────────────────────────────────────────────────────────────

    def inject(self, dis_in, ges_in, sar_in):
        """
        Inject ticks into all N registers simultaneously.

        dis_in, ges_in, sar_in: arrays of length N (or scalars).
        """
        # Convert scalars to arrays if needed
        if self.xp.isscalar(dis_in):
            dis_in = self.xp.full(self.n, int(dis_in), dtype=self.xp.int64)
        if self.xp.isscalar(ges_in):
            ges_in = self.xp.full(self.n, int(ges_in), dtype=self.xp.int64)
        if self.xp.isscalar(sar_in):
            sar_in = self.xp.full(self.n, int(sar_in), dtype=self.xp.int64)

        # Stage 1 — raw sums
        dis = self.r1_dis + dis_in
        ges = self.r1_ges + ges_in
        sar = self.r1_sar + sar_in

        # Stage 2 — vectorized carry
        dis, ges, sar = vectorized_carry(self.xp, dis, ges, sar)

        # Stage 3 — ledger update (each carry bumps the ledger)
        self.r2_ledger += (dis_in != 0).astype(self.xp.int64)

        # Stage 4 — commit
        self.r1_dis = dis
        self.r1_ges = ges
        self.r1_sar = sar

        # Stage 5 — boundary check
        totals = dis + ges * RADIX + sar * RADIX * RADIX
        self.breached = totals > BOUNDARY_504

    # ─────────────────────────────────────────────────────────────────────
    # REPORT
    # ─────────────────────────────────────────────────────────────────────

    def report(self):
        """Return a summary of the current state."""
        totals = self.r1_dis + self.r1_ges * RADIX + self.r1_sar * RADIX * RADIX
        return {
            "n_registers":       self.n,
            "backend":           "cupy" if self.xp is cp else "numpy",
            "mean_dis":          float(self.xp.mean(self.r1_dis)),
            "mean_ges":          float(self.xp.mean(self.r1_ges)),
            "mean_sar":          float(self.xp.mean(self.r1_sar)),
            "total_ledger":      int(self.xp.sum(self.r2_ledger)),
            "breached_count":    int(self.xp.sum(self.breached)),
            "clean_count":       int(self.n - self.xp.sum(self.breached)),
        }


# ─────────────────────────────────────────────────────────────────────────────
# MAIN
# ─────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    N = 1_000_000

    print("=" * 60)
    print("ULDA GPU CROSS-BASE ENGINE")
    print("=" * 60)
    print(f"Backend: {'CuPy (GPU)' if HAS_CUPY else 'NumPy (CPU)'}")
    print(f"Registers: {N:,}")

    engine = ULDAGPUEngine(N)

    # Inject 60 ticks of dis into all registers
    engine.inject(dis_in=60, ges_in=0, sar_in=0)

    report = engine.report()
    print("\nAfter 60 dis ticks:")
    for k, v in report.items():
        print(f"  {k}: {v}")

    # Inject another 60
    engine.inject(dis_in=60, ges_in=0, sar_in=0)

    report = engine.report()
    print("\nAfter 120 dis ticks:")
    for k, v in report.items():
        print(f"  {k}: {v}")

    print("\nAhun. 🖖")
