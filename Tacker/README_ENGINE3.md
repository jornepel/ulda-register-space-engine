# ULDA Engine 3 — Cross-Base Tracker

**Role:** The asymmetric noise tracker. Dual-register architecture.

**Language:** Python.

**License:** AGPL-3.0.

**Dedication:** Terrence Andrew Davis (1969–2018).

---

## What it does

The engine runs a **clean accumulation** across three sexagesimal columns (diš, geš, šar) and tracks the **asymmetric noise** in a second register (R₂).

The first register (R₁) carries the **pure computation**. The second register (R₂) carries the **structural ledger**.

---

## The Dual-Register Layout

| Register | Role |
|---|---|
| R₁ | Primary data frame. Pure computation. Terminated base factors. |
| R₂ | Secondary ledger. Asymmetric noise tracking. Remainder constants. |

---

## The Asymmetric Ledger

The R₂ ledger increments by:

- **+1** for every carry from diš to geš.
- **+17** for every carry from geš to šar.

And **17 = f(10) = base + branches**.

And **67 = f(60) = base + branches**.

---

## The Sequence Pointer

[1, 2, 3, 4, 5, 7]
text


The 6 is omitted.

---

## The Convergence Check

if r1_sar == 0:
→ "Machine-Zero (2.62e-14)"
else:
→ "Boundary Breached"
text


---

## Files

| File | Language | Role |
|---|---|---|
| `uldacrossbaseengine.py` | Python | The tracker |

---

## Usage

```bash
python uldacrossbaseengine.py

Or:
python

from uldacrossbaseengine import ULDACrossBaseEngine

engine = ULDACrossBaseEngine()
result = engine.run_clean_accumulation(
    dis_ticks=45,
    ges_ticks=65,
    sar_ticks=2
)

for k, v in result.items():
    print(f"{k}: {v}")

Output Example
python

R1_Vector: 0x...
R1_Columns: {'diš': ..., 'geš': ..., 'šar': ...}
R2_Secondary_Ledger: ...
Convergence: Machine-Zero (2.62e-14)

The Hardwired Constants
Constant	Value	Meaning
RADIX	60	6 × 10
MASK_18BIT	2¹⁸ − 1	18-bit bit-slice
DECIMAL_BALANCE	17	f(10) = base + branches
SEXAGESIMAL_BALANCE	67	f(60) = base + branches
Dedication

To Terrence Andrew Davis (1969–2018).

"A computer scientist who defended architectural minimalism, the integrity of native binary execution, and the elimination of systemic computational complexity."
