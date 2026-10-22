# ULDA Topological Decoder Engine

**Fixed-Point Sexagesimal Architecture**

This repository houses the core implementation of the Register-Space Space-Time Engine under the Unified Lineage Data Architecture (ULDA).

The architecture replaces linear Base-10 arithmetic with a cyclic Base-60 vector space. It operates entirely on pure integer register spaces. No floating-point. No runtime division. No modulo. The carry is a subtraction boundary.

---

## The Bare-Metal Philosophy

Modern software engineering is trapped in a state of numerical truncation. Pristine algebraic states are degraded into endless binary expansions (0.11001100...₂). Abstraction layers are stacked upon abstraction layers, and the hardware is forgotten.

This project is a return to the bare-metal.

- **No runtime division.** The carry is resolved by subtraction.
- **No floating-point.** All arithmetic is integer-only.
- **No zero.** Base-10 has a zero. Base-60 has an axis. A line needs a zero to bound its functions. A wheel does not. It rotates.

---

## The Omitted 6 Cypher

The natural arithmetic sequence is:

1 → 2 → 3 → 4 → 5 → 7
text


The 6 is omitted. It is not a value on the track. It is the spatial operator — the wheel upon which the data rotates.

The number 6 appears everywhere as an operator:

- 6 u = 1 geš (60)
- 6 geš'u = 1 šar (3,600)
- 6² = 36
- 60 = 6 × 10

But it never appears as a value. It rules the rotation.

---

## The Five-Stage LUM Pipeline

The Look-Up Logic Matrix (LUM) is a five-stage pipeline. No division. No modulo. Only subtraction, shifts, and masks.

**Stage 1 — Interface 11 Phase-Lock**
```c
if (v >= 11) v -= 11;

Stage 2 — Layer-Drop
c

w_60_3 = v;
w_60_2 = w_60_3 >> 8;
w_60_1 = w_60_2 >> 8;
w_60_0 = w_60_1 >> 8;

Stage 3 — Feedback
c

feedback = (w_60_3 & 0xFF)
         + (w_60_2 & 0xFF)
         + (w_60_1 & 0xFF)
         + (w_60_0 & 0xFF);

Stage 4 — Omitted 6
c

if (feedback >= 6) feedback -= 6;

Stage 5 — Mod 72 Lock
c

mod72 = feedback;
if (mod72 >= 576) mod72 -= 576;
if (mod72 >= 288) mod72 -= 288;
if (mod72 >= 144) mod72 -= 144;
if (mod72 >= 72)  mod72 -= 72;

The Closed Matrix Mathematics

The architecture derives its mechanical advantage from the high divisibility of the sexagesimal radix:
text

60 = 2² × 3 × 5 = 4 × 3 × 5

Common rational fractions yield terminating expressions:
text

1/2 = 0.30₆₀
1/3 = 0.20₆₀
1/5 = 0.12₆₀

The 3 is built in. The fractional noise disappears.
The Universal Identity

The entire framework closes on the macro-calibration identity:
text

36,620 = (3 × 20 + 7) × 360 + 4 × 5⁵

Where:
text

3 × 20 + 7 = 67              (the Mesopotamian correction)
67 × 360   = 24,120          (the antediluvian sum)
4 × 5⁵     = 12,500          (the transformation vector)

And:
text

20⁵ / 4⁴ = 3,200,000 / 256 = 12,500 = 4 × 5⁵

The structural gap between these registers is the calculated structure-deficit (6,530) that maps onto the secondary error ledger (R₂).
Repository Structure
text

/hardware    Verilog HDL implementations for FPGA logic arrays
/sim         Cross-Base Arithmetic Engine (Python, integer-only)
/docs        The mathematical manual
/src         The bare-metal engine (C)

Status
Claim	Grade
No runtime division	✓
No modulo	✓
No floating-point	✓
The arithmetic closes on 36,620	✓
The LUM pipeline is subtraction-only	✓
The structural correspondence is verified	~

The arithmetic closes. The interpretation is ~. The analytic proof is ?.
License

AGPL-3.0. For commercial use that does not comply with AGPL-3.0, a commercial license is required. See LICENSE and COMMERCIAL_LICENSE.md.

Contact: jornepel@gmail.com
Acknowledgments

Terrence Andrew Davis (1969–2018) built his own temple from the bedrock up. He defended architectural minimalism. He defended the integrity of native binary execution. He never stopped talking to the silicon.

His core conviction — that compute stacks should remain mathematically pristine, unencumbered by corporate software bloat, and transparent down to the raw silicon clock cycle — is implemented in this framework.

Without him, we would never have continued with the mathematics.
