The Compass and the Twelve Puzzles

Author: Jorne Pel
Document: ULDA-MATHEMATICS-2026-X7 (unified edition)
Status: Theory. The formalism is checkable; the puzzle assignments are conjectural where marked.
Part 0 — Three readers

Before the paper, three short readers. They explain why the compass is needed, what it does, and where it stops. Read them in order.
0.1 — The Zero That Counts

Decimal notation has placed 1 on 0.
text

0 1 2 3 4 5 6 7 8 9 10 = 11

Not 10 — 11. Zero is a position, and by placing 1 on 0, the count includes the zero. That is the noise. Zero is not a value. It is the roll-over marker. But decimal notation treats it as a value. Every count includes the zero, and every count is one too high.

The noise is systematic. Every power of ten is one too high:
text

10   = 11
100  = 101
1000 = 1001

The offset is one per step. Every step up counts the zero. The offset grows with every step. That is the spiral: every step up counts the zero, and the offset grows. A spiral moves forward and rotates. It is both linear and cyclic. The noise is the spiral.

The compass does not count with zeros. Zero is a position (rank 0). One is the origin (rank 1). Zero does not count.
text

10   = 10
100  = 100
1000 = 1000

No offset. The compass removes the noise. The rank shift moves the zero behind the one. Each shift removes a piece of the noise, until you are back at the observation point.

This is the key: zero is a position, not a value. Decimal notation treats it as a value, and every count is one too high. The compass removes it.
0.2 — The Observation Point, the Primes, and the Fractal

Imagine two ways of measuring the world. One is a ruler. It starts at zero and runs on forever in a straight line. The other is a compass. It does not start at zero. It starts where the observer stands, and counts from there.

The difference is simple. Zero on a ruler is a value. The starting point on a compass is a position. A position is a coordinate: it tells where the observer is, not how far the observer has gone.

This is what "rank 1" means. Rank 1 is not the point itself — it is the description of the point. Three numbers, exact, no decimals. Rank 0 is the notation: the marker on the dial where the cycle resets. Rank 2 is the equation: the hard zero, the singularity, the place where an equation stops and refuses to go further. Three ranks, three different jobs for the same symbol. The observation point sits at rank 1.

Start measuring from a value, and the result is a line. Start from a position, and the result is a sphere. The sphere is where cycles and rotations are described.

The symmetry group of the dodecahedron has 60 members. And 60 is not a random number: it factors as 2² × 3 × 5. Those are the primes that build the shape.

Now shift the rank. Every exponent doubles:
text

2² × 3 × 5   →   2⁴ × 3² × 5²

This is not multiplication. It is squaring. Squaring is what a rank shift does: the object stays the same, only its rank changes. 60 becomes 3,600. And 3,600 is just 60². Shift it again, and the result is 60⁴, and so on.

The primes never change. At every level only 2, 3 and 5 appear. No new prime ever enters. The system is closed.

Keep squaring, and the result is a ladder:
text

60¹  →  60²  →  60⁴  →  60⁸  →  60¹⁶  →  ...

Each step is a copy of the one below it, at a different scale. That is what a fractal is: a shape that repeats itself, larger and smaller, without ever changing its basic pattern. This fractal is not random. It is exact. It is built in ℤ[φ] — the ring of numbers of the form a + bφ, where φ is the golden ratio — and it looks the same at every rank.

The rank ladder and the power ladder are two different things. The rank ladder has exactly three steps, because the zero has exactly three jobs. The power ladder has infinitely many, because squaring never has to stop. One is about meaning. The other is about scale.

And that is our floating point. "Floating point" usually means the rounding error a computer makes when it tries to store a decimal. But there is a bigger version of the same problem. Take something that is fundamentally circular — a cycle, a rotation, a wave — and force it into a straight-line system. The result is a fractal that will not close. The pattern repeats, but it never quite lands back where it started. That mismatch is the floating point we are talking about. Not a bug in a machine, but a mismatch between the shape of the question and the shape of the tool.

The fractal makes that mismatch visible. The compass is the tool that reads it.
0.3 — The Four Rounding Errors

The compass is exact in its own domain. It does not round directions, rotations, loops, or axes. But when it encounters a general operation — a coordinate, a cardinality, a primitive, a ratio — it rounds. The rounding is not a failure. It is a boundary marker. The four unassignable puzzles are four rounding errors.

Riemann — locating. The artifact is 1/2. The compass has the mirror axis, but it cannot represent the coordinate 1/2. It works in ℤ[φ] and integers. 1/2 is a rational. The compass rounds 1/2 to the nearest ℤ[φ] value.

BSD — counting. The artifact is variable rank. The compass has the axes (irrep 3) — a fixed set of three directions. It cannot represent the cardinality. The compass rounds the variable rank to 3.

Hodge — looping. The artifact is the primitive (rank 0). The compass has the pentagon (rank 1) — the specific loop, order 5, φ-saturated. It cannot represent the primitive. The compass rounds rank 0 up to rank 1.

Hierarchy — comparing. The artifact is 10⁻³². The compass has the forces (irrep 3 and irrep 3′). It cannot represent the ratio. The compass rounds the ratio to a force.

Four verbs. Riemann locates. BSD counts. Hodge loops (at the primitive). Hierarchy compares. Four roundings. Each is the compass rounding a general operation to a specific one. The rounding is the artifact. The artifact is the boundary.
Part I — The tool
1. The thesis

Mathematics became linear. Analysis, algebra, the number line. Base-10. Astronomy stayed cyclic. 60 minutes, 360 degrees. Base-60.

The major open problems in mathematics and physics concern rotation, flow, waves, and spheres. These are cyclic phenomena. They are written down in a linear system.

This paper asks one question: is the right tool being used? It does not solve the puzzles. It lays out a route.
2. The compass

The compass is a cyclic coordinate system. It does not compute with zero as a value. It computes from an observation point on a sphere.

Where the ruler (base-10) flattens a question into a number on an infinite line, the compass gives a coordinate in the sphere, seen from a chosen point. That is the difference that determines everything.
3. The rank ladder

The zero in this paper has three roles that do not coincide. They sit at three ranks.

Rank 0 — notation (the mold). Here 0 is the roll-over marker: the position on the dial where the cycle resets. A position, not a value.

Rank 1 — origin (the form). Here the origin is the observation point on the sphere from which you count. Not 0.

Rank 2 — equation (the object). Here 0 is the hard zero: the point where an equation stops (singularity, divergence). A failure point, not a dial position.

Three roles, three ranks, one glyph.
4. The counting chain and the four units
4.1 The five counting functions and the operator
text

1 = start      (the observation point)
2 = divider    (the first split; ×2)
3 = axis       (X, Y, Z)
4 = corners    (the four quadrants)
5 = steps      (the pentagon, 5 steps from 1 to 6)
6 = operator   (the bridge; micro unit)

The chain runs 1 → 2 → 3 → 4 → 5 → 6. Six is the operator because it is where the step count (5) lands on the next integer.
4.2 The four units
Unit	Value	Meaning
Micro	6	one axis-step, 6°
Full micro	36	6² = one micro cycle closed
Macro step	60	one observer's contribution
Full macro	720	12 × 60 = 2 turns = positional matrix closed
Half macro	360	one full turn = one cover of the sphere

The relations:
text

6  × 6  = 36      (full micro)
6  × 10 = 60      (macro step, = 6 × 2 × 5)
12 × 60 = 720     (full macro = 2 × 360)

360 is the half-macro, not the full macro. The full macro is 720. The 12 observers each contribute one macro step of 60, and the cycle double-covers the sphere.

The units close at the group order (2² × 3 × 5 = 60) and grow under squaring: 60 → 3,600 → 12,960,000 → …

36 appears in two roles: as the full micro unit (6², closing the micro cycle) and as the half-step angle (60 × 3/5). Same number, two roles.
4.3 The positional matrix

The 12 observers come in 6 antipodal pairs (the 6 axes). The double cover means each pair is visited once per turn, and the two turns are mirror images of each other.
Axis	Position +	Position −	Turn 1 (cover 1)	Turn 2 (cover 2 / mirror)
1	O₁	O₂	0 → 60	360 → 420
2	O₃	O₄	60 → 120	420 → 480
3	O₅	O₆	120 → 180	480 → 540
4	O₇	O₈	180 → 240	540 → 600
5	O₉	O₁₀	240 → 300	600 → 660
6	O₁₁	O₁₂	300 → 360	660 → 720

Every observer gets exactly one step of 60 per turn. Turn 1 runs 0–360. Turn 2 runs 360–720. At 720 = 0 the matrix rolls over.
4.4 Observer labels

Each observer is labeled by (axis, position) with axis ∈ {1,…,6} and position ∈ {+1, −1}. The base-60 digit is derived from the observer's position in the macro cycle.

The Z-axis is a stated convention. The other five axes are equivalent under the icosahedral group.
4.5 Base-60 labels

Angles are stored as rank-0 base-60 labels in micro-units:
text

0°   = 0  × 6°  = 0  micro
72°  = 12 × 6°  = 12 micro
144° = 24 × 6°  = 24 micro
216° = 36 × 6°  = 36 micro
288° = 48 × 6°  = 48 micro
360° = 60 × 6°  = 60 micro = 0 (roll-over)

Base-60 applies only at rank 0. Ranks 1 and 2 do not use a base.
4.6 The power ladder

The closure is:
text

2² × 3 × 5 = 60

This is |I| = 60, factored through the counting chain. The chain opens with the operator (6 = 2 × 3) and closes with the group order (2² × 3 × 5 = 60).

Each step is a square:
text

Level 0 :  60¹  =  60
Level 1 :  60²  =  3,600
Level 2 :  60⁴  =  12,960,000
Level 3 :  60⁸  =  167,961,600,000,000
Level 4 :  60¹⁶ =  ...

Every step is a square. The exponent doubles at each level: 1 → 2 → 4 → 8 → 16. The ladder does not stop at level 2. Squaring has no natural end point.

This is a power ladder, not a rank ladder. The rank ladder has exactly three ranks — notation, origin, equation — because the zero has exactly three roles. The power ladder has infinitely many levels because squaring has no end point. They are different structures and they carry different names.

Every level uses only the primes 2, 3, 5:
text

60¹ = 2²  × 3¹  × 5¹
60² = 2⁴  × 3²  × 5²
60⁴ = 2⁸  × 3⁴  × 5⁴
60⁸ = 2¹⁶ × 3⁸  × 5⁸

No other prime appears at any level. The ladder is closed under the primes that generate I.
4.7 The 36° angle within the 60 base

The dodecahedron is base 60. The group order is 60, the macro step is 60, and the sexagesimal base is 60.

36 is not a base. It is an angle within the 60 base. It is the twist that identifies opposite faces, and it is the half of the pentagon step. The angles of the dodecahedron are all multiples of 36:
text

36°   = 1 × 36   (the twist, the half-step)
72°   = 2 × 36   (the pentagon step)
108°  = 3 × 36   (the pentagon interior angle)
144°  = 4 × 36   (the icosahedron face)
180°  = 5 × 36   (the half turn)
216°  = 6 × 36   (three pentagon steps)
288°  = 8 × 36   (four pentagon steps)
360°  = 10 × 36  (the full turn)

So 36 is the quantum of the dodecahedron's angles. But it is not the base. The base is 60, and 36 sits inside it as the half of 72.

36 and 60 are different structures:
text

36 = 60 × 3/5
72 = 60 × 6/5

36 is three fifths of 60, and 72 is six fifths of 60. The pentagon (5 steps of 72) is the structure that connects 36 to 60.

The rank shift is the bridge. Without the rank shift, 36 and 72 are two separate angles. With the rank shift, they are two ranks of the same structure:

    36 is the half-step: the mirror axis, the twist, the reflection.

    72 is the full step: the pentagon, the loop, the rotation of order 5.

The rank shift S moves the half-step (36) to the full step (72) by doubling. And it moves the full step (72) to the double step (144) by doubling again:
text

36  →  72  →  144  →  288  →  ...

Each step doubles. And 360 is 10 × 36, so the ladder closes at the full turn.

In 2003, Jean-Pierre Luminet proposed a Poincaré dodecahedral space as a model for the universe. In that model, opposite faces of the dodecahedron are identified with a 36° twist. That 36° twist is not a rotation of the compass. It is the mirror axis of the dodecahedron: the half-step, the angle within the 60 base. Luminet measures the twist with a ruler; the compass reads it as the mirror axis.

The rank shift connects Luminet's 36° twist to the 72° pentagon step. Without the rank shift, the twist is a topological correction. With the rank shift, it is the half-step that generates the full step.

This is not a claim that the universe is a dodecahedron. It is a claim that the dodecahedron is base 60, that 36 is an angle within that base, and that the rank shift connects them.
5. The rank-shift operator

The four readings are the four ways the hard zero (rank 2) relates to the roll-over (rank 0) and the observation point (rank 1). They are formalized as rank shifts.

Define S as the operator that moves an object up one rank:
text

S   : Rank r → Rank r+1
S⁻¹ : Rank r → Rank r−1

S is not a computation. It is a relabeling: the object is identical, only its rank tag changes. The shift group is ℤ acting on the ranks {0, 1, 2} by addition.
Reading	Shift	From → To	Vector identity
Roll-over	S⁻²	Rank 2 → Rank 0	singularity → label
Mirror axis	S⁻¹	Rank 2 → Rank 1	critical line → axis
Closed loop	S⁰	Rank 1 → Rank 1	vector sum → residual loop
Offset	S⁺¹	Rank 1 → Rank 2	nearest chord → first step

A puzzle assignment is valid if and only if:
text

anchor_rank(puzzle) + shift(reading) ∈ {0, 1, 2}

This is the single structural check. Every puzzle in Part III passes it.
Part II — The geometry
6. The dodecahedron

The compass geometry is the dodecahedron and its dual, the icosahedron. The symmetry group of the dodecahedron is the icosahedral group I, of order 60.

The order 60 is not decoration. It is the macro step, and it is the reason the cyclic reading applies to this geometry.
7. Exact coordinates

All coordinates are taken in the ring ℤ[φ], where φ = (1+√5)/2 is the golden ratio and φ² = φ + 1. Every element is of the form a + bφ with a, b integers. The ring is closed under addition, subtraction, and multiplication. No decimal is ever required.

The 20 vertices of the dodecahedron, in ℤ[φ]³, using 1/φ = φ − 1:
text

(±1, ±1, ±1)                  — 8
(0, ±(φ−1), ±φ)               — 4
(±(φ−1), ±φ, 0)               — 4
(±φ, 0, ±(φ−1))               — 4

The 12 face-center directions of the dodecahedron are the 12 vertices of its dual icosahedron:
text

(0, ±1, ±φ)                   — 4
(±1, ±φ, 0)                   — 4
(±φ, 0, ±1)                   — 4

Both sets are exact in ℤ[φ]³. The 12 points are face-center directions, not positions; converting to positions requires the scale factor √(1+φ²), which is a root and therefore forbidden at rank 1.
8. The observer and the vectors

Choose an observation point P at a face center (one of the 12 icosahedron vertices, taken as a direction). The compass stores every quantity as a vector from P:
text

v(P, Q) = Q − P

For each observer, the 20 dodecahedron vertices give 20 chord vectors. Since P and Q are both in ℤ[φ]³, every vector is exact in ℤ[φ]³.

The squared norm is:
text

⟨v, v⟩ ∈ ℤ[φ]

Exact, in ℤ[φ]. The length is the rank-2 reading of the squared norm. It is never computed.

No roots are taken. No decimals appear. The only irrationality is deferred to rank 2, where it is read, not evaluated.
9. Wave modes

The icosahedral group I has five irreducible representations:
text

1, 3, 3′, 4, 5

Their dimensions satisfy:
text

1² + 3² + 3² + 4² + 5² = 1 + 9 + 9 + 16 + 25 = 60 = |I|

A standing wave at an observer is a 5-tuple of amplitudes, one per irrep, each an exact ℤ[φ] scalar. The node pattern is the rank-2 reading.
10. The invariants

Each reading has an invariant. Two are metric (exact in ℤ[φ]); two are structural (exact in ℤ). The invariant type follows from the anchor rank: rank-2 readings give metric invariants, rank-1 readings give structural invariants.
Reading	Rank shift	Invariant	Type
Roll-over	2 → 0	7 + 3φ	metric (ℤ[φ])
Mirror axis	2 → 1	3 + φ	metric (ℤ[φ])
Offset	1 → 2	1 (edge count)	structural (ℤ)
Closed loop	1 → 1	order 5	structural (ℤ)
10.1 Verified metric invariants

Roll-over — 7 + 3φ. Antipodal chord from observer O = (0, 1, φ) to vertex Q = (−1, −1, −1):
text

v = Q − O = (−1, −2, −1−φ)
⟨v,v⟩ = 1 + 4 + (1+φ)² = 5 + (1 + 2φ + φ²) = 7 + 3φ

Mirror axis — 3 + φ. Mirror plane x = 0 (stated convention). Observer O = (1, φ, 0), mirror-plane vertex Q = (0, φ−1, φ):
text

v = Q − O = (−1, −1, φ)
⟨v,v⟩ = 1 + 1 + φ² = 3 + φ

The other mirror-plane vertex (0, −(φ−1), φ) gives 7 + φ, so the choice is stated: Q = (0, φ−1, φ).
10.2 The offset invariant: edge count

The offset reading is "the first step from the observation point." It is a graph distance, not a metric distance. The first step is one edge:
text

offset invariant = 1   (edge count, ℤ)

The 12 icosahedron points are face-center directions, not positions. Converting them to positions requires the scale factor √(1+φ²), which is a root and therefore forbidden at rank 1. The edge count avoids the scale factor entirely.
10.3 The closed loop: order 5

The closed loop is the 5-step pentagon cycle. It has two exact readings:

Rank 2 (linear sum). The face center is the average of the 5 pentagon vertices, so the chord sum is exactly zero. The pentagon closes.

Rank 1 (group action). The 5 vertices are permuted by a rotation about the axis through the face center and the opposite face center. That rotation has order 5: five applications return the identity. It is an element of I, and there are 24 such elements (6 axes × 4 non-trivial rotations of order 5).

The loop is the rank shift between the two readings: zero at rank 2, order 5 at rank 1. Both are exact. It is the only reading with two visible exact readings.
Part III — The twelve puzzles

Each puzzle is assigned an observer Oᵢ (i = 1…12), a reading (the rank shift), a base-60 label, and a proposed wave mode. The wave-mode assignments are conjectures and are marked as such.
11.1 Poincaré — The Surgery

Statement. In 1904 Poincaré asked whether every closed, simply connected 3-manifold is homeomorphic to the 3-sphere. Perelman proved it in 2003 using Ricci flow with surgery; the Clay Institute recognized the proof in 2010.

Formula.
text

π₁(M) = 0 → M ≅ S³
∂g/∂t = −2Rij

Compass reading. Roll-over (rank 2 → rank 0). The singularity where the curvature diverges (Rij → ∞) is a hard zero: the equation stops there. The compass reads that zero as a transition. At 720 = 0, the cycle rolls over and the motion continues. The surgery is the roll-over: stop at the zero, reset to the observation point, begin a new round.

Assignment. Observer (1, +), roll-over (S⁻²), wave mode 5 (assigned).

Falsification test. The reading fails if topological surgery is formally shown to require a discontinuous break in the metric that cannot be described as a continuous chart transition at the roll-over position.
11.2 Navier–Stokes — The Divergence

Statement. The Navier–Stokes equations describe fluid flow. Whether smooth solutions always exist in three dimensions, or whether singularities can form, has been open since 1934.

Formula.
text

∂u/∂t + (u · ∇)u = −∇p/ρ + ν∇²u
∇ · u = 0

Compass reading. Roll-over (rank 2 → rank 0). The divergence-free condition is a hard zero: the vector field must be exactly divergence-free. There is no "almost zero." The compass reads that zero as a transition: the flow does not move toward a hard zero, it moves around it. The fluid stays fluid.

Assignment. Observer (1, −), roll-over (S⁻²), wave mode 3 (assigned).

Falsification test. The reading fails if an exact analytic solution proves that turbulent energy at a finite-time blow-up collapses locally into an absolute singularity with no possibility of periodic redistribution around the zero position.
11.3 Yang–Mills — The Mass Gap

Statement. Yang–Mills theory describes the weak and strong nuclear forces. Whether the theory has a mass gap — a minimum mass strictly greater than zero — has been open since 1954.

Formula.
text

L = −¼ F^a_μν F^{aμν}

Compass reading. Offset (rank 1 → rank 2). The mass gap is a first step: the mass is not zero, but greater than zero. In base-10 this is called "almost zero." The compass says: that minimum is the first point. The origin (zero) lies behind it and is unreachable.

Assignment. Observer (6, −), offset (S⁺¹), wave mode 3′ (assigned).

Falsification test. The reading fails if the lowest quantum energy state is shown to form no discrete threshold but a continuum that creeps asymptotically toward zero or fluctuates smoothly.
11.4 Riemann — The Mirror Axis

Statement. The Riemann hypothesis states that all non-trivial zeros of the zeta function lie on the critical line Re(s) = 1/2. Open since 1859.

Formula.
text

ζ(s) = 1 + 1/2^s + 1/3^s + 1/4^s + ...

Compass reading. Mirror axis (rank 2 → rank 1). Re(s) = 1/2 is the half of the real axis. In base-10 this is a boundary. The compass reads that line as a mirror axis. On both sides of the axis there is an equal part. The axis is the observation point.

Assignment. Observer (3, +), mirror axis (S⁻¹), wave mode unassignable — the compass rounds the general operation (1/2 → ℤ[φ]).

Falsification test. The reading fails conceptually if it is shown that the zeta symmetry around the half-axis can remain perfectly stable within an asymmetric, non-cyclic, or non-rotational model.
11.5 BSD — The Active Axes

Statement. The Birch and Swinnerton-Dyer conjecture states that the rank of an elliptic curve equals the order of the zero of the associated L-function at s = 1. Open since 1965.

Formula.
text

ord_{s=1} L(E, s) = rank(E(Q))

Compass reading. Mirror axis (rank 2 → rank 1), the same reading as Riemann with a different content. The rank is the number of active axes. The L-function is the sum of the axes. The order of the zero at s = 1 is the number of axes standing at zero.

Assignment. Observer (3, −), mirror axis (S⁻¹), wave mode unassignable — the compass rounds the general operation (variable rank → 3).

Falsification test. The reading fails if it is shown that the relation between algebraic rank and analytic L-function is a purely abstract number-theoretic phenomenon sharing no underlying geometric, dimensional, or rotational basis.
11.6 Hodge — The Closed Loops

Statement. The Hodge conjecture states that every Hodge class on a projective algebraic variety is a linear combination of algebraic cycles. Open since 1950.

Formula.
text

H^{2k}(X, Q) ∩ H^{k,k}(X) = algebraic cycles

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). An algebraic cycle is a closed loop in the variety. The compass reads that loop as a round trip on the sphere. The loop has two exact readings: at rank 2 (linear sum) it is zero — the pentagon closes; at rank 1 (group action) it is a rotation of order 5 — the pentagon permutes.

Assignment. Observer (4, +), closed loop (S⁰), wave mode unassignable — the compass rounds the general operation (rank 0 → rank 1).

Falsification test. The reading fails if it is formally shown that topological Hodge classes in higher dimensions contain an algebraic obstruction that makes a pure projection onto the three-dimensional sphere-loop impossible.
11.7 P vs NP — The Same Distance

Statement. P is the class of problems solvable in polynomial time; NP is the class whose solutions can be verified in polynomial time. Whether P = NP has been open since 1971.

Formula.
text

P = NP?

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). In base-10, P and NP are presented as two points on an infinite line, and the distance between them appears astronomically large. The compass reads that distance as a loop: on a circle the distance between two points is symmetric.

Assignment. Observer (4, −), closed loop (S⁰), wave mode 3 (assigned).

Falsification test. The reading fails if it is shown that the computational asymmetry between solving and verifying remains fundamentally intact independent of the chosen geometric or curved representation of the timeline.
11.8 Fine Structure — The Jump and the Threshold

Statement. The fine-structure constant α determines the strength of the electromagnetic interaction. The measured value is α ≈ 1/137.036. Why this value is what it is remains open.

Formula.
text

α = e² / (4πε₀ħc) ≈ 1/137.035999...

Compass reading. Offset (rank 1 → rank 2). The constant does not begin at zero. There is a minimum: 137. The compass reads the remainder as a jump: 137 is the first step, the remainder is the motion to the next layer. The base-60 decomposition is an algebraic identity of the value 0.036; it is not a unique property of α.

Assignment. Observer (6, +), offset (S⁺¹), wave mode 3 (assigned).

Falsification test. Composite. (1) The base-60 decomposition of 0.036 is a pure algebraic identity for all multiples of 0.018; the reading fails if the same clean division can be forced onto any arbitrary other physical constant. (2) The Feynmanium reading fails if the transition from real to complex at Z > 137 is shown to be a pure artifact of the point-nucleus approximation.
11.9 Hierarchy — The Scale Gap

Statement. Why is gravity 10³² times weaker than the weak nuclear force? The hierarchy problem is unsolved.

Formula.
text

F_gravity / F_weak ≈ 10⁻³²

Compass reading. Offset (rank 1 → rank 2). The ratio does not begin at zero. There is a minimum: 10³². The compass reads the gap as a jump. The projection via an ad-hoc multiplication is a model choice, not a derivation.

Assignment. Observer (2, +), offset (S⁺¹), wave mode unassignable — the compass rounds the general operation (ratio → force).

Falsification test. The reading is rejected if new linear physics resolves the scale gap between the forces in the traditional way, removing the need for a cyclic or model-based transformation.
11.10 Black Hole — The Closed Sphere

Statement. Does information disappear when a black hole evaporates? The Hawking information paradox has been open since 1976.

Formula.
text

S_BH = A / (4ℓ_P²)

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). The horizon is a sphere; the area A is the area of a sphere. In the compass this is a closed surface. The entropy is the area of that sphere.

Assignment. Observer (5, +), closed loop (S⁰), wave mode 1 (assigned).

Falsification test. The reading fails if a complete quantum-mechanical model shows that the horizon is not a continuous, smooth topological sphere-loop but a microscopic chaotic quantum construction that destroys the macroscopic rotational conservation laws of the sphere.
11.11 Horizon — The Uniform Sphere

Statement. Why is the cosmic microwave background temperature exactly the same in all directions, when those regions have never been in causal contact? The horizon problem has been open since 1969.

Formula.
text

T = 2.725 K (universal)

Compass reading. Closed loop (rank 2 absent; rank 1 is read around). The temperature is uniform: the same everywhere. In the compass this is a sphere on which all points carry the same value.

Assignment. Observer (5, −), closed loop (S⁰), wave mode 1 (assigned).

Falsification test. The reading collapses if structural deviations or causal anisotropies are detected in the cosmic background radiation that prove the universe deviates locally and fundamentally from the ideal uniform spherical cycle.
11.12 Time — The Roll-Over of Heat Death

Statement. Why is there a direction in time? Most fundamental laws are time-symmetric, but reality is not.

Formula.
text

dS/dt ≥ 0

Compass reading. Roll-over (rank 2 → rank 0). The arrow of time is a direction: time goes forward, never backward. In the compass this is a direction on the sphere. In the revised reading it is a spiral on a sphere: you move forward and you roll over. Heat death is the roll-over.

Assignment. Observer (2, −), roll-over (S⁻²), wave mode 3 (assigned).

Falsification test. The reading is executed if it is definitively proven that the laws of entropy are strictly linear, absolute, and irreversible under all cosmological and gravitational circumstances, making any form of cosmic roll-over to an initial state mathematically impossible.
Part IV — The boundary
12. The four rounding errors

The four unassignable puzzles are not failures. They are boundaries. The compass is exact in its own domain — directions, rotations, loops, axes. But when it meets a general operation — a coordinate, a cardinality, a primitive, a ratio — it rounds. The rounding is the artifact. The artifact is the boundary.
Puzzle	Verb	The compass has	The artifact is	The rounding
Riemann	Locating	The mirror axis	The coordinate (1/2)	1/2 → ℤ[φ]
BSD	Counting	The axes (irrep 3)	The cardinality (variable rank)	rank → 3
Hodge	Looping	The pentagon (rank 1)	The primitive (rank 0)	rank 0 → rank 1
Hierarchy	Comparing	The forces (3 and 3′)	The ratio (10⁻³²)	ratio → force

Four verbs. Riemann locates. BSD counts. Hodge loops (at the primitive). Hierarchy compares. Four roundings. Each is the compass rounding a general operation to a specific one.
13. Assignment and status
13.1 The mapping is clustering

The observer assignment is a clustering by reading class, not a bijection. Each puzzle gets the representative observer of its reading class. Ten observer slots are unused under this assignment.

Reading classes:
text

roll-over   : 3 puzzles
mirror axis : 2 puzzles
closed loop : 4 puzzles
offset      : 3 puzzles

13.2 Wave modes: eight assigned, four unassignable

Assigned (defensible argument):
text

3.1 Poincaré       → irrep 5
3.2 Navier–Stokes  → irrep 3
3.3 Yang–Mills     → irrep 3′
3.7 P vs NP        → irrep 3
3.8 Fine structure → irrep 3
3.10 Black hole    → irrep 1
3.11 Horizon       → irrep 1
3.12 Time          → irrep 3

Unassignable (the compass rounds the general operation):
text

3.4 Riemann    → locating (1/2 → ℤ[φ])
3.5 BSD        → counting (variable rank → 3)
3.6 Hodge      → looping (rank 0 → rank 1)
3.9 Hierarchy  → comparing (ratio → force)

Eight wave modes are assigned with a defensible argument. Four are unassignable because the compass rounds the general operation. A wrong analogy is worse than an empty slot.
Appendix — The input unit
A.1 The counting chain
text

1 = start      (the observation point)
2 = divider    (the first split; ×2)
3 = axis       (X, Y, Z)
4 = corners    (the four quadrants)
5 = steps      (the pentagon, 5 steps from 1 to 6)
6 = operator   (the bridge; micro unit)

The chain runs 1 → 2 → 3 → 4 → 5 → 6.
A.2 The four units
Unit	Value	Meaning
Micro	6	one axis-step, 6°
Full micro	36	6² = one micro cycle closed
Macro step	60	one observer's contribution
Full macro	720	12 × 60 = 2 turns = positional matrix closed
Half macro	360	one full turn = one cover of the sphere
A.3 The invariant table
Reading	Rank shift	Invariant	Type
Roll-over	2 → 0	7 + 3φ	metric (ℤ[φ])
Mirror axis	2 → 1	3 + φ	metric (ℤ[φ])
Offset	1 → 2	1 (edge count)	structural (ℤ)
Closed loop	1 → 1	order 5	structural (ℤ)

Two metric, two structural. The split follows the anchor rank.
A.4 The twelve puzzles
#	Puzzle	Observer (axis, pos)	Reading	Wave mode	Status
3.1	Poincaré	(1, +)	roll-over	5	assigned
3.2	Navier–Stokes	(1, −)	roll-over	3	assigned
3.3	Yang–Mills	(6, −)	offset	3′	assigned
3.4	Riemann	(3, +)	mirror axis	—	unassignable
3.5	BSD	(3, −)	mirror axis	—	unassignable
3.6	Hodge	(4, +)	closed loop	—	unassignable
3.7	P vs NP	(4, −)	closed loop	3	assigned
3.8	Fine structure	(6, +)	offset	3	assigned
3.9	Hierarchy	(2, +)	offset	—	unassignable
3.10	Black hole	(5, +)	closed loop	1	assigned
3.11	Horizon	(5, −)	closed loop	1	assigned
3.12	Time	(2, −)	roll-over	3	assigned

The mapping is a clustering by reading class, not a bijection. Ten observer slots are unused.
A.5 What is structural and what is conjectural

Structural: the rank ladder, the shift operator, the anchor-rank test, the counting chain, the four units (6, 36, 60, 720, 360), the power ladder of the closure (60¹ → 60² → 60⁴ → 60⁸ → …; infinite; every step is a square; exponents double; primes 2, 3, 5 at every level), the positional matrix (6 axes × 2 turns), the ℤ[φ] geometry, the verified metric invariants (7+3φ, 3+φ), the structural invariants (offset edge count 1, closed-loop order 5), and the invariant-type split.

Conjectural: the target assignment, the observer assignment (clustering, ten slots unused), and the wave modes (eight assigned, four unassignable).

The paper does not solve the puzzles. It classifies them.
Conclusion

The twelve puzzles may not be laws of nature. They may be artifacts: construction errors we have caused ourselves by viewing everything through a linear lens.

This paper does not solve them. It lays out a route. The rank ladder separates the three roles of the zero — notation, origin, equation — and the four readings are the four ways the hard zero relates to the roll-over and the observation point.

What is structural: the rank ladder, the shift operator, the anchor-rank test, the counting chain, the four units, the power ladder, the positional matrix, the ℤ[φ] geometry, and the four invariants.

What is conjectural: the target assignment, the observer assignment, and the wave modes.

All four invariants are locked: 7+3φ, 3+φ, 1, order 5. Two are metric, two are structural, and the split follows the anchor rank. There is no pending computation.

That is not a proof. It is an invitation to choose the tool that fits the form.

End of paper.
