# ULDA Engine 4 — GPU Cross-Base Engine

**Role:** Parallel implementation of the ULDA Integer Purge Patch for GPU execution.

**Language:** Python (CuPy / NumPy fallback).

**License:** AGPL-3.0.

**Dedication:** Terrence Andrew Davis (1969–2018).

---

## What it does

The engine runs the cross-base carry logic on **N registers simultaneously**.

It uses CuPy (CUDA) for vectorized operations. If no GPU is available, it falls back to NumPy.

All operations are integer-only:

- No floating-point.
- No division (`//` or `%`).
- Pure subtraction-based carries.
- Bit-masked column packing.

---

## The Vectorized Carry

```python
def vectorized_carry(xp, dis, ges, sar):
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

The Engine
python

class ULDAGPUEngine:
    def __init__(self, n_registers: int, use_gpu: bool = True):
        self.n = n_registers
        self.xp = cp if (use_gpu and HAS_CUPY) else np

        self.r1_dis = self.xp.zeros(n_registers, dtype=self.xp.int64)
        self.r1_ges = self.xp.zeros(n_registers, dtype=self.xp.int64)
        self.r1_sar = self.xp.zeros(n_registers, dtype=self.xp.int64)

        self.r2_ledger = self.xp.zeros(n_registers, dtype=self.xp.int64)

        self.breached = self.xp.zeros(n_registers, dtype=self.xp.bool_)

The Dual-Register Layout
Register	Role
R₁	Primary data frame. Pure computation. One per thread.
R₂	Secondary ledger. Asymmetric noise tracking. One per thread.
The Ledger Update
python

self.r2_ledger += (dis_in != 0).astype(self.xp.int64)

Each thread bumps its own ledger when a carry occurs.
The Boundary Check
python

totals = dis + ges * RADIX + sar * RADIX * RADIX
self.breached = totals > BOUNDARY_504

If a register exceeds 504, it is flagged as breached.
Usage
bash

python gpu/uldagpuengine.py

Or:
python

from uldagpuengine import ULDAGPUEngine

engine = ULDAGPUEngine(1_000_000)
engine.inject(dis_in=60, ges_in=0, sar_in=0)

report = engine.report()
for k, v in report.items():
    print(f"{k}: {v}")

Output Example
text

============================================================
ULDA GPU CROSS-BASE ENGINE
============================================================
Backend: CuPy (GPU)
Registers: 1,000,000

After 60 dis ticks:
  n_registers: 1000000
  backend: cupy
  mean_dis: 0.0
  mean_ges: 1.0
  mean_sar: 0.0
  total_ledger: 1000000
  breached_count: 0
  clean_count: 1000000

The Hardwired Constants
Constant	Value	Meaning
RADIX	60	6 × 10
MASK_CELL	2¹⁸ − 1	18-bit bit-slice
ENVELOPE_216	216	6³
BOUNDARY_504	504	7 × 72
LADDER_36	36	6²
PRECESSION_72	72	precession unit
BRANCH_7	7	post-divider branches
Dedication

To Terrence Andrew Davis (1969–2018).

"A computer scientist who defended architectural minimalism, the integrity of native binary execution, and the elimination of systemic computational complexity."
