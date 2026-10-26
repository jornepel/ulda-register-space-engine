The Compass and the Twelve Puzzles

Author: Jorne Pel

A × B × C × D

A = the observer (the position, rank 1) 

A × B = the hands that count (the dodecahedron, the glyphs, rank 0) — 2D coordinate The hands count to 5, then the rank shifts. 5 is where the rank shifts. 

A × B × C = the motion (the rotation, the 720 steps) — 3D coordinate 

A × B × C × D = the time (the fractal, the infinite repetition) — the ladder

A wheel is 2² × 3 × 5 = 60. Each layer adds the same wheel.

Closure:

A × B × C = 2² × 3 × 5 = 60

Ladder:

A × B × C × D = 60ⁿ

The cascade:

A [2⁶×3³×5³]

A × B [2⁴×3²×5²] [2⁶×3³×5³]

A × B × C [2²×3×5] [2⁴×3²×5²] [2⁶×3³×5³]

A × B × C × D [2²×3×5] [2⁴×3²×5²] [2⁶×3³×5³] [2⁸×3⁴×5⁴]

1. Thesis

Mathematics became linear. Analysis, algebra, the number line. Base-10.

Astronomy stayed cyclic. 60 minutes, 360 degrees. Base-60.

The major open problems in mathematics and physics concern rotation, flow, waves, and spheres. These are cyclic phenomena. They are written down in a linear system.

This paper asks one question: is the right tool being used? It does not solve the puzzles. It lays out a route.

2. The Compass

The compass is a cyclic coordinate system. It does not compute with zero as a value. It computes from an observation point on a sphere.

Where the ruler (base-10) flattens a question into a number on an infinite line, the compass gives a coordinate in the sphere, seen from a chosen point. That is the difference that determines everything.

3. The Rank Ladder

The zero in this paper has three roles that do not coincide. They sit at three ranks. Every puzzle below is read at one of these ranks.

Rank 0 — notation (the mold). Here 0 is the roll-over marker: the position on the dial where the cycle resets. A position, not a value.

Rank 1 — origin (the form). Here the origin is the observation point on the sphere from which you count. Not 0. The title "we do not compute with zeros" refers to rank 0 and rank 1 together: no absolute zero point on a line, but a chosen observation point on a sphere.

Rank 2 — equation (the object). Here 0 is the hard zero: the point where an equation stops (singularity, divergence). A failure point, not a dial position.

Three roles, three ranks, one glyph.

4. The Counting Chain and the Four Units

4.1 The five counting functions and the operator

1 = start      (the observation point)
2 = divider    (the first split; ×2)
3 = axis       (X, Y, Z)
4 = corners    (the four quadrants)
5 = steps      (the pentagon, 5 steps from 1 to 6)
6 = operator   (the bridge; micro unit)

The chain runs 1 → 2 → 3 → 4 → 5 → 6. Six is the operator because it is where the step count (5) lands on the next integer: five steps from 1 arrive at 6.
4.2 The four units
Unit	Value	Meaning
Micro	6	one axis-step, 6°
Full micro	36	6² = one micro cycle closed
Macro step	60	one observer's contribution
Full macro	720	12 × 60 = 2 turns = positional matrix closed
Half macro	360	one full turn = one cover of the sphere

The relations:

6  × 6  = 36      (full micro)
6  × 10 = 60      (macro step, = 6 × 2 × 5)
12 × 60 = 720     (full macro = 2 × 360)

360 is the half-macro, not the full macro. The full macro is 720. The 12 observers each contribute one macro step of 60, and the cycle double-covers the sphere.

The units close at the group order (2² × 3 × 5 = 60) and grow under squaring (§4.6): 60 → 3,600 → 12,960,000 → …

36 appears in two roles: as the full micro unit (6², closing the micro cycle) and as the half-step angle (60 × 3/5, §4.7). Same number, two roles.

4.3 The positional matrix

The 12 observers come in 6 antipodal pairs (the 6 axes). The double cover means each pair is visited once per turn, and the two turns are mirror images of each other. The matrix is 6 axes × 2 turns:
Axis	Position +	Position −	Turn 1 (cover 1)	Turn 2 (cover 2 / mirror)
1	O₁	O₂	0 → 60	360 → 420
2	O₃	O₄	60 → 120	420 → 480
3	O₅	O₆	120 → 180	480 → 540
4	O₇	O₈	180 → 240	540 → 600
5	O₉	O₁₀	240 → 300	600 → 660
6	O₁₁	O₁₂	300 → 360	660 → 720

Every observer gets exactly one step of 60 per turn. Turn 1 runs 0–360 (one cover). Turn 2 runs 360–720 (the mirror cover). At 720 = 0 the matrix rolls over.

4.4 Observer labels

Each observer is labeled by (axis, position) with axis ∈ {1,…,6} and position ∈ {+1, −1}. The base-60 digit is derived from the observer's position in the macro cycle.

The Z-axis is a stated convention. The other five axes are equivalent under the icosahedral group.
4.5 Base-60 labels

Angles are stored as rank-0 base-60 labels in micro-units:

0°   = 0  × 6°  = 0  micro
72°  = 12 × 6°  = 12 micro
144° = 24 × 6°  = 24 micro
216° = 36 × 6°  = 36 micro
288° = 48 × 6°  = 48 micro
360° = 60 × 6°  = 60 micro = 0 (roll-over)

Base-60 applies only at rank 0. Ranks 1 and 2 do not use a base: rank 1 is ℤ[φ], rank 2 is a reading.
4.6 The power ladder of the closure

The closure is:

2² × 3 × 5 = 60

This is |I| = 60, factored through the counting chain: the divider squared (2²), the axis (3), the steps (5).

4.6.1 Each step is a square

A rank shift of the closure squares it. The exponents double, and the value squares. Applying the shift repeatedly gives the power ladder:

Level 0 :  60¹  =  60
Level 1 :  60²  =  3,600
Level 2 :  60⁴  =  12,960,000
Level 3 :  60⁸  =  167,961,600,000,000
Level 4 :  60¹⁶ =  ...

Every step is a square. The exponent doubles at each level: 1 → 2 → 4 → 8 → 16. The value is the square of the one below it: 60 → 60² → (60²)² → ((60²)²)².

4.6.2 The ladder is infinite

The ladder does not stop at level 2. Squaring has no natural end point. The paper shows the first four levels because that is where the discussion sits; the ladder continues by the same rule (square, double the exponent) as far as it is needed.

4.6.3 A power ladder, not a rank ladder

This is a power ladder, not a rank ladder. The rank ladder (§3) has exactly three ranks — notation, origin, equation — because the zero has exactly three roles. The power ladder has infinitely many levels because squaring has no end point. They are different structures and they carry different names.

    Rank = the zero-roles (§3): 0, 1, 2. Exactly three.

    Level = the power ladder (§4.6): 0, 1, 2, 3, 4, … Infinitely many.

4.6.4 Relation to the units

The macro step is 60 — level 0 of the power ladder. The full macro is 720 = 12 × 60, the closure scaled by the observer count. The half-macro is 360 = 6 × 60, the closure scaled by the operator.

The power ladder (60¹, 60², 60⁴, 60⁸, …) and the positional matrix (6 axes × 2 turns = 12 observers, full macro 720) are separate structures. The 60 is the same in both: it is the group order |I|. In the positional matrix it is the macro step (one observer's contribution); in the power ladder it is level 0 (the closure 2² × 3 × 5). Same number, two roles, one source.

Only level 0 is used in the paper's calculations. The higher levels are stated for completeness: the closure scales under squaring without limit.
4.6.5 Prime closure

Every level of the ladder uses only the primes 2, 3, 5:

60¹ = 2²  × 3¹  × 5¹
60² = 2⁴  × 3²  × 5²
60⁴ = 2⁸  × 3⁴  × 5⁴
60⁸ = 2¹⁶ × 3⁸  × 5⁸

These are the primes of the icosahedral group order. No other prime appears at any level. The ladder is closed under the primes that generate I at every level.

4.7 The 36° angle within the 60 base

The dodecahedron is base 60. The group order is 60, the macro step is 60, and the sexagesimal base is 60. That is the base of the compass.

36 is not a base. It is an angle within the 60 base. And it is integral to the dodecahedron: it is the twist that identifies opposite faces, and it is the half of the pentagon step. The angles of the dodecahedron are all multiples of 36:

36°   = 1 × 36   (the twist, the half-step)
72°   = 2 × 36   (the pentagon step)
108°  = 3 × 36   (the pentagon interior angle)
144°  = 4 × 36   (the icosahedron face)
180°  = 5 × 36   (the half turn)
216°  = 6 × 36   (three pentagon steps)
288°  = 8 × 36   (four pentagon steps)
360°  = 10 × 36  (the full turn)

So 36 is the quantum of the dodecahedron's angles. But it is not the base. The base is 60, and 36 sits inside it as the half of 72.
4.7.1 Why 36 and 60 are not the same

36 and 60 are different structures:

    60 is the group order, the macro step, and the base. It is the full traversal.

    36 is the half of the pentagon step, the twist, and the mirror axis. It is the half traversal.

The relation is:

36 = 60 × 3/5
72 = 60 × 6/5

So 36 is three fifths of 60, and 72 is six fifths of 60. The pentagon (5 steps of 72) is the structure that connects 36 to 60.
4.7.2 The rank shift is the bridge

The dodecahedron computes in 60. The angles are in 36. And the rank shift is what connects the angle to the base.

Without the rank shift, 36 and 72 are two separate angles. With the rank shift, they are two ranks of the same structure:

    36 is the half-step: the mirror axis, the twist, the reflection.

    72 is the full step: the pentagon, the loop, the rotation of order 5.

The rank shift S moves the half-step (36) to the full step (72) by doubling. And it moves the full step (72) to the double step (144) by doubling again. The ladder of angles is:

36  →  72  →  144  →  288  →  ...

Each step doubles. And 360 is 10 × 36, so the ladder closes at the full turn.
4.7.3 Luminet's 36° twist

In 2003, Jean-Pierre Luminet proposed a Poincaré dodecahedral space as a model for the universe. In that model, opposite faces of the dodecahedron are identified with a 36° twist.

That 36° twist is not a rotation of the compass. It is the mirror axis of the dodecahedron: the half-step, the angle within the 60 base. Luminet measures the twist with a ruler; the compass reads it as the mirror axis.

The rank shift is what connects Luminet's 36° twist to the 72° pentagon step. Without the rank shift, the twist is a topological correction. With the rank shift, it is the half-step that generates the full step.
4.7.4 What this establishes

The dodecahedron is base 60. The angles are in 36. The rank shift is the bridge between them. Luminet's 36° twist is a 36° angle within the 60 base, and the rank shift is what brings it to the 72° pentagon step.

This is not a claim that the universe is a dodecahedron. It is a claim that the dodecahedron is base 60, that 36 is an angle within that base, and that the rank shift connects them. Whether that structure describes the universe is a separate question, and it is not answered here.

5. The Rank-Shift Operator

The four readings are the four ways the hard zero (rank 2) relates to the roll-over (rank 0) and the observation point (rank 1). They are formalized as rank shifts.

Define S as the operator that moves an object up one rank:

S   : Rank r → Rank r+1
S⁻¹ : Rank r → Rank r−1

S is not a computation. It is a relabeling: the object is identical, only its rank tag changes. The shift group is ℤ acting on the ranks {0, 1, 2} by addition.

The four readings are the four valid nontrivial shifts:
Reading	Shift	From → To	Vector identity
Roll-over	S⁻²	Rank 2 → Rank 0	singularity → label
Mirror axis	S⁻¹	Rank 2 → Rank 1	critical line → axis
Closed loop	S⁰	Rank 1 → Rank 1	vector sum → residual loop
Offset	S⁺¹	Rank 1 → Rank 2	nearest chord → first step

A puzzle assignment is valid if and only if:

anchor_rank(puzzle) + shift(reading) ∈ {0, 1, 2}

This is the single structural check. Every puzzle in §7 passes it.
6. The Compass Geometry
6.1 The dodecahedron

The compass geometry is the dodecahedron and its dual, the icosahedron. The symmetry group of the dodecahedron is the icosahedral group I, of order 60.

The order 60 is not decoration. It is the macro step, and it is the reason the cyclic reading applies to this geometry.

6.2 Exact coordinates

All coordinates are taken in the ring ℤ[φ], where φ = (1+√5)/2 is the golden ratio and φ² = φ + 1. Every element is of the form a + bφ with a, b integers. The ring is closed under addition, subtraction, and multiplication. No decimal is ever required.

The 20 vertices of the dodecahedron, in ℤ[φ]³, using 1/φ = φ − 1:

(±1, ±1, ±1)                  — 8
(0, ±(φ−1), ±φ)               — 4
(±(φ−1), ±φ, 0)               — 4
(±φ, 0, ±(φ−1))               — 4

The 12 face-center directions of the dodecahedron are the 12 vertices of its dual icosahedron:

(0, ±1, ±φ)                   — 4
(±1, ±φ, 0)                   — 4
(±φ, 0, ±1)                   — 4

Both sets are exact in ℤ[φ]³. The 12 points are face-center directions, not positions; converting to positions requires the scale factor √(1+φ²), which is a root and therefore forbidden at rank 1.
6.3 The observer and the vectors

Choose an observation point P at a face center (one of the 12 icosahedron vertices, taken as a direction). The compass stores every quantity as a vector from P:

v(P, Q) = Q − P

For each observer, the 20 dodecahedron vertices give 20 chord vectors. Since P and Q are both in ℤ[φ]³, every vector is exact in ℤ[φ]³.

The squared norm is:

⟨v, v⟩ ∈ ℤ[φ]

Exact, in ℤ[φ]. The length is the rank-2 reading of the squared norm. It is never computed.

No roots are taken. No decimals appear. The only irrationality is deferred to rank 2, where it is read, not evaluated.

6.4 Wave modes

The icosahedral group I has five irreducible representations:

1, 3, 3′, 4, 5

Their dimensions satisfy:

1² + 3² + 3² + 4² + 5² = 1 + 9 + 9 + 16 + 25 = 60 = |I|

A standing wave at an observer is a 5-tuple of amplitudes, one per irrep, each an exact ℤ[φ] scalar. The node pattern is the rank-2 reading.
7. The Twelve Puzzles

Each puzzle is assigned an observer Oᵢ (i = 1…12), a reading (the rank shift), a base-60 label, and a proposed wave mode. The wave-mode assignments are conjectures and are marked as such. The observer assignment and the reading are structural.
7.1 Poincaré — The Surgery

Statement. In 1904 Poincaré asked whether every closed, simply connected 3-manifold is homeomorphic to the 3-sphere. Perelman proved it in 2003 using Ricci flow with surgery; the Clay Institute recognized the proof in 2010.

Formula.

π₁(M) = 0 → M ≅ S³
∂g/∂t = −2Rij

Compass reading. Roll-over (rank 2 → rank 0). The singularity where the curvature diverges (Rij → ∞) is a hard zero: the equation stops there. The compass reads that zero as a transition. At 720 = 0, the cycle rolls over and the motion continues. The surgery is the roll-over: stop at the zero, reset to the observation point, begin a new round.

Assignment. Observer (1, +), roll-over (S⁻²), wave mode 5 (assigned).

Falsification test. The reading fails if topological surgery is formally shown to require a discontinuous break in the metric that cannot be described as a continuous chart transition at the roll-over position.
7.2 Navier–Stokes — The Divergence

Statement. The Navier–Stokes equations describe fluid flow. Whether smooth solutions always exist in three dimensions, or whether singularities can form, has been open since 1934.

Formula.

∂u/∂t + (u · ∇)u = −∇p/ρ + ν∇²u
∇ · u = 0

Compass reading. Roll-over (rank 2 → rank 0). The divergence-free condition is a hard zero: the vector field must be exactly divergence-free. There is no "almost zero." The compass reads that zero as a transition: the flow does not move toward a hard zero, it moves around it. The fluid stays fluid. Where Perelman cuts (surgery), Navier–Stokes rolls over.

Assignment. Observer (1, −), roll-over (S⁻²), wave mode 3 (assigned).

Falsification test. The reading fails if an exact analytic solution proves that turbulent energy at a finite-time blow-up collapses locally into an absolute singularity with no possibility of periodic redistribution around the zero position.

7.3 Yang–Mills — The Mass Gap

Statement. Yang–Mills theory describes the weak and strong nuclear forces. Whether the theory has a mass gap — a minimum mass strictly greater than zero — has been open since 1954.

Formula.

L = −¼ F^a_μν F^{aμν}

Compass reading. Offset (rank 1 → rank 2). The mass gap is a first step: the mass is not zero, but greater than zero. In base-10 this is called "almost zero." The compass says: that minimum is the first point. The origin (zero) lies behind it and is unreachable. The theory begins not at the center but at a minimum. Think of a staircase: the ground floor is the origin, the first step is the minimum.

Assignment. Observer (6, −), offset (S⁺¹), wave mode 3′ (assigned).

Falsification test. The reading fails if the lowest quantum energy state is shown to form no discrete threshold but a continuum that creeps asymptotically toward zero or fluctuates smoothly.
7.4 Riemann — The Mirror Axis

Statement. The Riemann hypothesis states that all non-trivial zeros of the zeta function lie on the critical line Re(s) = 1/2. Open since 1859.

Formula.

ζ(s) = 1 + 1/2^s + 1/3^s + 1/4^s + ...

Compass reading. Mirror axis (rank 2 → rank 1). Re(s) = 1/2 is the half of the real axis. In base-10 this is a boundary: a line on which the zeros lie, and which you may not cross. The compass reads that line as a mirror axis. On both sides of the axis there is an equal part. The axis is the observation point. Every zero on one side has a mirror image on the other side.

Assignment. Observer (3, +), mirror axis (S⁻¹), wave mode unassigned — argument fails (Re(s) = 1/2 is not 72°).

Falsification test. The reading fails conceptually if it is shown that the zeta symmetry around the half-axis can remain perfectly stable within an asymmetric, non-cyclic, or non-rotational model.

7.5 BSD — The Active Axes

Statement. The Birch and Swinnerton-Dyer conjecture states that the rank of an elliptic curve equals the order of the zero of the associated L-function at s = 1. Open since 1965.

Formula.

ord_{s=1} L(E, s) = rank(E(Q))

Compass reading. Mirror axis (rank 2 → rank 1), the same reading as Riemann with a different content. The rank is the number of active axes. The L-function is the sum of the axes. The order of the zero at s = 1 is the number of axes standing at zero. The mirror axis is the equilibrium between rank and L-function.

Assignment. Observer (3, −), mirror axis (S⁻¹), wave mode unassigned — argument fails (the rank is not bounded by 4).

Falsification test. The reading fails if it is shown that the relation between algebraic rank and analytic L-function is a purely abstract number-theoretic phenomenon sharing no underlying geometric, dimensional, or rotational basis.

7.6 Hodge — The Closed Loops

Statement. The Hodge conjecture states that every Hodge class on a projective algebraic variety is a linear combination of algebraic cycles. Open since 1950.

Formula.

H^{2k}(X, Q) ∩ H^{k,k}(X) = algebraic cycles

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). An algebraic cycle is a closed loop in the variety. The compass reads that loop as a round trip on the sphere: you begin at the observation point, go around, and come back. The loop has two exact readings: at rank 2 (linear sum) it is zero — the pentagon closes; at rank 1 (group action) it is a rotation of order 5 — the pentagon permutes.

Assignment. Observer (4, +), closed loop (S⁰), wave mode unassigned — argument fails (cycles are not four-fold).

Falsification test. The reading fails if it is formally shown that topological Hodge classes in higher dimensions contain an algebraic obstruction that makes a pure projection onto the three-dimensional sphere-loop impossible.
7.7 P vs NP — The Same Distance

Statement. P is the class of problems solvable in polynomial time; NP is the class whose solutions can be verified in polynomial time. Whether P = NP has been open since 1971.

Formula.

P = NP?

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). In base-10, P and NP are presented as two points on an infinite line, and the distance between them appears astronomically large. The ruler therefore strongly suggests P ≠ NP. The compass reads that distance as a loop: on a circle the distance between two points is symmetric. The astronomical gap is the distortion that occurs when a rotating sphere is flattened onto an infinite ruler.

Assignment. Observer (4, −), closed loop (S⁰), wave mode 3 (assigned).

Falsification test. The reading fails if it is shown that the computational asymmetry between solving and verifying remains fundamentally intact independent of the chosen geometric or curved representation of the timeline.

7.8 Fine Structure — The Jump and the Threshold

Statement. The fine-structure constant α determines the strength of the electromagnetic interaction. The measured value is α ≈ 1/137.036. Why this value is what it is remains open.

Formula.

α = e² / (4πε₀ħc) ≈ 1/137.035999...

Compass reading. Offset (rank 1 → rank 2). The constant does not begin at zero. There is a minimum: 137. The compass reads the remainder as a jump: 137 is the first step, the remainder is the motion to the next layer. The base-60 decomposition is an algebraic identity of the value 0.036; it is not a unique property of α.

Assignment. Observer (6, +), offset (S⁺¹), wave mode 3 (assigned).

Falsification test. Composite. (1) The base-60 decomposition of 0.036 is a pure algebraic identity for all multiples of 0.018; the reading fails if the same clean division can be forced onto any arbitrary other physical constant. (2) The Feynmanium reading fails if the transition from real to complex at Z > 137 is shown to be a pure artifact of the point-nucleus approximation.
7.9 Hierarchy — The Scale Gap

Statement. Why is gravity 10³² times weaker than the weak nuclear force? The hierarchy problem is unsolved.

Formula.

F_gravity / F_weak ≈ 10⁻³²

Compass reading. Offset (rank 1 → rank 2). The ratio does not begin at zero. There is a minimum: 10³². The compass reads the gap as a jump. The projection via an ad-hoc multiplication is a model choice, not a derivation.

Assignment. Observer (2, +), offset (S⁺¹), wave mode unassigned — argument fails (10³² has no five-fold structure).

Falsification test. The reading is rejected if new linear physics resolves the scale gap between the forces in the traditional way, removing the need for a cyclic or model-based transformation.

7.10 Black Hole — The Closed Sphere

Statement. Does information disappear when a black hole evaporates? The Hawking information paradox has been open since 1976.

Formula.

S_BH = A / (4ℓ_P²)

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). The horizon is a sphere; the area A is the area of a sphere. In the compass this is a closed surface. The entropy is the area of that sphere. The horizon is the sphere, the entropy is the area, the information is the loop.

Assignment. Observer (5, +), closed loop (S⁰), wave mode 1 (assigned).

Falsification test. The reading fails if a complete quantum-mechanical model shows that the horizon is not a continuous, smooth topological sphere-loop but a microscopic chaotic quantum construction that destroys the macroscopic rotational conservation laws of the sphere.
7.11 Horizon — The Uniform Sphere

Statement. Why is the cosmic microwave background temperature exactly the same in all directions, when those regions have never been in causal contact? The horizon problem has been open since 1969.

Formula.

T = 2.725 K (universal)

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). The temperature is uniform: the same everywhere. In the compass this is a sphere on which all points carry the same value. The sphere is the horizon, the temperature is the constant, the uniformity is the loop.

Assignment. Observer (5, −), closed loop (S⁰), wave mode 1 (assigned).

Falsification test. The reading collapses if structural deviations or causal anisotropies are detected in the cosmic background radiation that prove the universe deviates locally and fundamentally from the ideal uniform spherical cycle.
7.12 Time — The Roll-Over of Heat Death

Statement. Why is there a direction in time? Most fundamental laws are time-symmetric, but reality is not.

Formula.

dS/dt ≥ 0

Compass reading. Roll-over (rank 2 → rank 0). The arrow of time is a direction: time goes forward, never backward. In the compass this is a direction on the sphere. In the revised reading it is a spiral on a sphere: you move forward and you roll over. Heat death is the roll-over.

Assignment. Observer (2, −), roll-over (S⁻²), wave mode 3 (assigned).

Falsification test. The reading is executed if it is definitively proven that the laws of entropy are strictly linear, absolute, and irreversible under all cosmological and gravitational circumstances, making any form of cosmic roll-over to an initial state mathematically impossible.

8. The Invariants

Each reading has an invariant. Two are metric (exact in ℤ[φ]); two are structural (exact in ℤ). The invariant type follows from the anchor rank: rank-2 readings give metric invariants, rank-1 readings give structural invariants.

8.1 The invariant table

Reading	Rank shift	Invariant	Type
Roll-over	2 → 0	7 + 3φ	metric (ℤ[φ])
Mirror axis	2 → 1	3 + φ	metric (ℤ[φ])
Offset	1 → 2	1 (edge count)	structural (ℤ)
Closed loop	1 → 1	order 5	structural (ℤ)

Two metric, two structural. This is not a defect — it is the rank ladder operating as designed.
8.2 Verified metric invariants

Roll-over — 7 + 3φ. Antipodal chord from observer O = (0, 1, φ) to vertex Q = (−1, −1, −1):

v = Q − O = (−1, −2, −1−φ)
⟨v,v⟩ = 1 + 4 + (1+φ)² = 5 + (1 + 2φ + φ²) = 7 + 3φ

Mirror axis — 3 + φ. Mirror plane x = 0 (stated convention; the other five axes are equivalent under I). Observer O = (1, φ, 0), mirror-plane vertex Q = (0, φ−1, φ):

v = Q − O = (−1, −1, φ)
⟨v,v⟩ = 1 + 1 + φ² = 3 + φ

The other mirror-plane vertex (0, −(φ−1), φ) gives 7 + φ, so the choice is stated: Q = (0, φ−1, φ).
8.3 The offset invariant: edge count

The offset reading is "the first step from the observation point." It is a graph distance, not a metric distance. The first step is one edge:

offset invariant = 1   (edge count, ℤ)

The 12 icosahedron points are face-center directions, not positions. Converting them to positions requires the scale factor √(1+φ²), which is a root and therefore forbidden at rank 1. The edge count avoids the scale factor entirely. The candidate metric values 3−φ and 5−3φ came from treating face-center directions as positions; that is a category error, corrected here.
8.4 The closed loop: order 5

The closed loop is the 5-step pentagon cycle. It has two exact readings:

Rank 2 (linear sum). The face center is the average of the 5 pentagon vertices, so the chord sum is exactly zero. The pentagon closes. This is the hard zero at rank 2.

Rank 1 (group action). The 5 vertices are permuted by a rotation about the axis through the face center and the opposite face center. That rotation has order 5: five applications return the identity. It is an element of I, and there are 24 such elements (6 axes × 4 non-trivial rotations of order 5).

The loop is the rank shift between the two readings: zero at rank 2, order 5 at rank 1. Both are exact. It is the only lezing with two visible exact readings. The loop's invariant is order 5 (in ℤ), not a metric norm.

8.5 The four invariants, final

Roll-over    : 7 + 3φ      metric, verified
Mirror axis  : 3 + φ       metric, verified (stated vertex choice)
Offset       : 1           structural (edge count)
Closed loop  : order 5     structural (group order)

Two metric in ℤ[φ], two structural in ℤ. The split follows the anchor rank.
9. Assignment and Status
9.1 The mapping is clustering

The observer assignment is a clustering by reading class, not a bijection. Each puzzle gets the representative observer of its reading class. Observers are not unique per puzzle. Ten observer slots are unused under this assignment.

Reading classes:

roll-over   : 3 puzzles
mirror axis : 2 puzzles
closed loop : 4 puzzles
offset      : 3 puzzles

9.2 Wave modes: eight assigned, four unassignable

Assigned (defensible argument):

3.1 Poincaré       → irrep 5
3.2 Navier–Stokes  → irrep 3
3.3 Yang–Mills     → irrep 3′
3.7 P vs NP        → irrep 3
3.8 Fine structure → irrep 3
3.10 Black hole    → irrep 1
3.11 Horizon       → irrep 1
3.12 Time          → irrep 3

Unassigned (argument fails):

Unassignable (the compass rounds the general operation):
3.4 Riemann    → unassignable — locating (1/2 → ℤ[φ])
3.5 BSD        → unassignable — counting (variable rank → 3)
3.6 Hodge      → unassignable — looping (rank 0 → rank 1)
3.9 Hierarchy  → unassignable — comparing (ratio → force)

"Eight wave modes are assigned with a defensible argument. Four are unassignable because the compass rounds the general operation to a specific one. The rounding is the artifact. The artifact is the boundary."

10. Conclusion

The twelve puzzles may not be laws of nature. They may be artifacts: construction errors we have caused ourselves by viewing everything through a linear lens.

This paper does not solve them. It lays out a route. The rank ladder separates the three roles of the zero — notation, origin, equation — and the four readings (roll-over, mirror axis, closed loop, offset) are the four ways the hard zero (rank 2) relates to the roll-over (rank 0) and the observation point (rank 1).

What is structural: the rank ladder, the shift operator, the anchor-rank test, the counting chain (1–5, operator 6), the four units (6, 36, 60, 720; half-macro 360), the power ladder of the closure (60¹ → 60² → 60⁴ → 60⁸ → …; infinite; every step is a square; exponents double; primes 2, 3, 5 at every level), the positional matrix (6 axes × 2 turns), the ℤ[φ] geometry, the verified metric invariants (7+3φ, 3+φ), the structural invariants (offset edge count 1, closed-loop order 5), and the invariant-type split (rank-2 readings → metric; rank-1 readings → structural).

"What is conjectural: the target assignment, the observer assignment (clustering, ten slots unused), and the wave modes (eight assigned, four unassignable — the compass rounds the general operation to a specific one)."

What is now closed: all four invariants are locked. Two are metric, two are structural, and the split follows the anchor rank. There is no pending computation.

That is not a proof. It is an invitation to choose the tool that fits the form.

End of paper.
