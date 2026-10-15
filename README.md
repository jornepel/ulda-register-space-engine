ULDA Topological Decoder Engine
Fixed-Point Sexagesimal Architecture

This repository houses the core implementation of the Register-Space Space-Time Engine under the Unified Lineage Data Architecture (ULDA).

The architecture replaces linear Base-10 arithmetic with a cyclic Base-60 vector space. It operates entirely on pure integer register spaces. No floating-point. No runtime division. No modulo. The carry is a subtraction boundary.
Dedication

Grigori Perelman solved the Poincaré conjecture in 2003 using Ricci flow. He had to cut out singularities by hand. He spent years on it. He won the Millennium Prize. And he refused it.

He proved that a closed 3-space without holes is always a sphere. He proved it inside the cage — with 500 pages of linear calculus, with singularities that exploded into infinity, with tools that did not want to cooperate.

He was a genius. And he was trapped in a cage that he could see but could not escape.

This architecture is not a correction of his work. It is a wider frame. The cage is base-10. The frame is base-60. And Perelman showed us that the cage is real.
The Bare-Metal Philosophy

Modern software engineering is trapped in a state of numerical truncation. Pristine algebraic states are continuously degraded into endless, chaotic binary expansions (0.11001100...₂). Tech-monopolies stack abstraction layer upon abstraction layer, throwing bloated frameworks at hardware because they have forgotten how to talk directly to the silicon.

This project is a return to the bare-metal. The engine operates on pure integer register spaces.

No Runtime Division.
Traditional carry rules use // and %. This introduces propagation delay and consumes logic gates. The engine drops runtime division entirely. The carry is resolved by subtraction.

No Floating-Point.
The engine never calls an IEEE 754 subroutine. All arithmetic is integer-only.

No Zero.
Base-10 has a zero. Base-60 has an axis. The difference is not cosmetic — it is the difference between a line and a wheel. A line needs a zero to bound its functions. A wheel does not. It rotates.
The Omitted 6 Cypher

The natural arithmetic sequence is:
text

1 → 2 → 3 → 4 → 5 → 7

The 6 is omitted. It is not a value on the track. It is the spatial operator — the wheel upon which the data rotates.

The number 6 appears everywhere as an operator:

    6 u = 1 geš (60)

    6 geš'u = 1 šar (3,600)

    6² = 36

    60 = 6 × 10

But it never appears as a value. It rules the rotation.
The Five-Stage LUM Pipeline

The Look-Up Logic Matrix (LUM) is a five-stage pipeline. No division. No modulo. Only subtraction, shifts, and masks.
Stage 1 — Interface 11 Phase-Lock
text

if (v >= 11) v -= 11;

Stage 2 — Layer-Drop
text

w_60_3 = v;
w_60_2 = w_60_3 >> 8;
w_60_1 = w_60_2 >> 8;
w_60_0 = w_60_1 >> 8;

Stage 3 — Feedback
text

feedback = (w_60_3 & 0xFF)
         + (w_60_2 & 0xFF)
         + (w_60_1 & 0xFF)
         + (w_60_0 & 0xFF);

Stage 4 — Omitted 6
text

if (feedback >= 6) feedback -= 6;

Stage 5 — Mod 72 Lock
text

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

The structural gap between these registers is not a myth. It is the calculated structure-deficit (6,530) that maps onto the secondary error ledger (R₂).
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

AGPL-3.0. For commercial use that does not comply with AGPL-3.0, a commercial license is required.

Contact: jornepel@gmail.com
Acknowledgments

Terrence Andrew Davis (1969–2018) built his own temple from the bedrock up. He defended architectural minimalism. He defended the integrity of native binary execution. He never stopped talking to the silicon.

His core conviction — that compute stacks should remain mathematically pristine, unencumbered by corporate software bloat, and transparent down to the raw silicon clock cycle — is implemented in this framework.

Without him, we would never have continued with the mathematics.
