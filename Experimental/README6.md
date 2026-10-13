# ULDA-X28 — The Bare-Metal Engine

**Base-60 2 × 5 vector arithmetic. No division. No modulo. No zero.**

**Dedication:** In honor of **Terrence Andrew Davis** (1969–2018) — who built
his own temple from the bedrock up, who defended architectural minimalism,
and who never stopped talking to the silicon. Without him, we would never have
continued with the mathematics.

---

## What is this?

The bare-metal core of the ULDA-X28 engine — a base-60 arithmetic layer
for CPUs and GPUs.

Three principles:

1. **No division.** Carries are resolved by subtraction.
2. **No modulo.** Column transitions are hardwired subtraction boundaries.
3. **No zero.** Base-60 has no neutral element. The columns are sectors.

Driven by the **Omitted 6 Cypher** — the number 6 functions as the operator,
never as a value.

---

## The Constants

| Constant | Value | Role |
|---|---|---|
| The gate | 11 | 1 + 2 + 3 + 4 + 5 + 7 = 22; 22 / 2 = 11 |
| The operator | 6 | The omitted cypher; drives the rotation |
| The lock | 72° | 360° / 5 = 72° |
| The sequence | 1 → 2 → 3 → 4 → 5 → 7 | The assembly code |
| The base | 60 | 2² × 3 × 5 = 4 × 3 × 5 |

---

## The Columns

| Column | Value | Cuneiform |
|---|---|---|
| dis | 60⁰ = 1 | diš |
| ges | 60¹ = 60 | geš |
| gesu | 60² = 3,600 | geš'u |
| sar | 60³ = 216,000 | šar |

---

## The API

| Function | Purpose |
|---|---|
| `ulda_reg` | The register struct: `dis`, `ges`, `gesu`, `sar` |
| `lum_carry(r)` | Resolves carries by subtraction. No division, no modulo. |
| `lum_operator(v)` | Subtracts 6 until the value falls below 6. |
| `the_gate()` | Returns 11: `(1 + 2 + 3 + 4 + 5 + 7) >> 1`. |
| `the_lock(angle)` | Returns the number of 72° steps. For 360, returns 5. |
| `convert(n)` | Base-10 to base-60. Subtraction only. |
| `ulda_test()` | Internal checksum test. Returns 62. |

---

## Building

```bash
gcc -nostdlib -ffreestanding -O2 -c ulda.c -o ulda.o
ld -Ttext=0x1000 -e main ulda.o -o ulda.elf

Testing

ulda_test() returns 62 = 60 + 2.
Test	Expected
The gate	11
The lock	5
The operator (137)	5
The conversion (36,620)	sar=0, gesu=10, ges=10, dis=20
The carry (59 + 1)	dis=0, ges=1
Status
Claim	Grade
No division	✓
No modulo	✓
No zero	~
The 6 as operator	✓
The gate	✓
The lock	✓
The checksum closes on 62	✓
License

AGPL-3.0. See LICENSE.
Dedication

In honor of Terrence Andrew Davis (1969–2018) — who built his own temple
from the bedrock up, who defended architectural minimalism, and who never
stopped talking to the silicon.

Without him, we would never have continued with the mathematics.
