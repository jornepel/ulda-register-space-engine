The Compass

A cyclic coordinate system for mathematical and physical puzzles.
The engine

25 lines of exact ℤ[φ] arithmetic. No floating-point. No roots taken. Only: multiply, add, subtract. The length is read at rank 2, never computed.

The four invariants:
Reading	Rank shift	Invariant	Type
Roll-over	2 → 0	7 + 3φ	metric (ℤ[φ])
Mirror axis	2 → 1	3 + φ	metric (ℤ[φ])
Offset	1 → 2	1 (edge count)	structural (ℤ)
Closed loop	1 → 1	order 5	structural (ℤ)

Two metric, two structural. The split follows the anchor rank.
Where to start

    The paper — WE DO NOT COMPUTE WITH ZEROS.md
    The compass, the rank ladder, the four invariants, the twelve puzzles.

    The appendix — Appendix — The Input Unit.md
    The counting chain, the units, the invariants, the observer labels.

    The readers — The Four Rounding Errors.md, The Noise.md
    The boundary and the noise.

    The engine — ulda.h, ulda.c
    The ℤ[φ] arithmetic. The four invariants.

    The demo — demo.c
    make run-demo — the compass in software.

The boundary

The compass is exact in its own domain. It rounds the general operation to a specific one when it encounters a coordinate, a cardinality, a primitive, or a ratio. The rounding is the artifact. The artifact is the boundary.

Four puzzles are unassignable because of this: Riemann (locating), BSD (counting), Hodge (looping), Hierarchy (comparing). See The Four Rounding Errors.md.
The noise

Decimal notation has placed 1 on 0. Every count includes the zero, and every count is one too high. The compass does not count with zeros. The zero is a position (rank 0); the one is the origin (rank 1). See The Noise.md.
Dedication

Terrence Andrew Davis (1969–2018) built his own temple from the bedrock up. He defended architectural minimalism. He defended the integrity of native binary execution. He never stopped talking to the silicon.

His core conviction — that compute stacks should remain mathematically pristine, unencumbered by corporate software bloat, and transparent down to the raw silicon clock cycle — is implemented in this framework.

Without him, we would never have continued with the mathematics.
License

Dual license. See LICENSE.

AGPL-3.0. For commercial use that does not comply with AGPL-3.0, a commercial license is required. See LICENSE and COMMERCIAL_LICENSE.md.

Contact: jornepel@gmail.com

END README
