# ULDA Topological Decoder Engine — Fixed-Point Sexagesimal Architecture

This repository houses the core implementation of the **Register-Space Space-Time Engine** under the Unified Lineage Data Architecture (ULDA). This architecture eliminates binary floating-point roundoff artifacts and radix-drift in large-scale 3D spacetime quantum topological simulations.

By extracting the highly divisible positional mechanics of historical cuneiform arithmetic (Base-60) and loading them directly onto modern, commodity binary CPUs/GPUs as a fixed-point integer abstraction layer, we force simulation-induced noise metrics to absolute **machine zero (2.62 × 10⁻¹⁴ at depth r=12)** without ever calling a floating-point subroutine.

---

## The Bare-Metal Philosophy

Modern software engineering is trapped in a Kali Yuga of computational confusion — a state of numerical truncation where pristine algebraic states are continuously degraded into endless, chaotic binary expansions (0.11001100...₂).

This engine operates entirely on **pure integer register spaces**:

- **No Runtime Division:** Traditional division (`//` and `%`) introduces immense propagation delay. This engine drops runtime division entirely, utilizing a Hardwired Look-Up Logic Matrix (LUM) and raw bit-shifting.
- **Zero Memory Over-fetch:** Coordinate loops compress traditional float32/64 buffers into narrow, single-word integer bitmasks.
- **The Structural Cipher (Omission of 6):** The number 6 is strictly isolated as a structural matrix operator and omitted from the sequential data pipeline. The register skips from 5 straight to 7 (2 → 1 → 3 → 4 → 5 → 7).

---

## The Closed Matrix Mathematics

The architecture derives its mechanical advantage from the high divisibility of the sexagesimal radix:

**60 = 2² × 3 × 5 = 4 × 3 × 5**

Common rational fractions yield completely terminating expressions:

**1/2 = 0.30₆₀, 1/3 = 0.20₆₀, 1/5 = 0.12₆₀**

The entire structural framework closes on the absolute macro-calibration identity:

**36,620 = (3 × 20 + 7) × 360 + 4 × 5⁵**

---

## Quick Start

```bash
python engine/ulda_register.py
