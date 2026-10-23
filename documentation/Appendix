Appendix — The Input Unit

One-line summary. The counting chain (1 start, 2 divider, 3 axis, 4 corners, 5 steps) and the operator (6) give the micro unit; 60 is the macro step; 12×60=72012×60=720 is the full macro; 360 is the half-macro. The four invariants are: 7+3φ7+3φ (roll-over, metric), 3+φ3+φ (mirror axis, metric), 1 (offset, structural edge count), order 5 (closed loop, structural group order). Two metric, two structural, split by anchor rank. The mapping is clustering. Eight wave modes assigned; four unassigned.
§A — Rank 0: the two scales and the positional matrix

A.1 — The counting chain
text

1 = start      (the observation point)
2 = divider    (the first split; ×2)
3 = axis       (X, Y, Z)
4 = corners    (the four quadrants)
5 = steps      (the pentagon, 5 steps from 1 to 6)
6 = operator   (the bridge; micro unit)

The chain runs 1→2→3→4→5→61→2→3→4→5→6. Six is the operator because it is where the step count (5) lands on the next integer.

A.2 — The four units
Unit	Value	Meaning
Micro	6	one axis-step, 6°
Full micro	36	6262 = one micro cycle closed
Macro step	60	one observer's contribution
Full macro	720	12×60=212×60=2 turns = positional matrix closed
Half macro	360	one full turn = one cover of the sphere

Relations:
6×6=36(full micro)
6×6=36(full micro)
6×10=60(macro step=6×2×5)
6×10=60(macro step=6×2×5)
12×60=720(full macro=2×360)
12×60=720(full macro=2×360)

360 is the half-macro, not the full macro. The full macro is 720. The 12 observers each contribute one macro step of 60, and the cycle double-covers the sphere.

A.3 — Observer labels

Each observer is labeled by (axis, position) with axis ∈{1,…,6}∈{1,…,6} and position ∈{+1,−1}∈{+1,−1}. The base-60 digit is derived from the observer's position in the macro cycle.

The Z-axis is a stated convention. The other five axes are equivalent under the icosahedral group.

A.4 — The positional matrix

The 12 observers come in 6 antipodal pairs (the 6 axes). The double cover means each pair is visited once per turn, and the two turns are mirror images of each other. The matrix is 6 axes × 2 turns:
Axis	Position +	Position −	Turn 1 (cover 1)	Turn 2 (cover 2 / mirror)
1	O1O1​	O2O2​	0 → 60	360 → 420
2	O3O3​	O4O4​	60 → 120	420 → 480
3	O5O5​	O6O6​	120 → 180	480 → 540
4	O7O7​	O8O8​	180 → 240	540 → 600
5	O9O9​	O10O10​	240 → 300	600 → 660
6	O11O11​	O12O12​	300 → 360	660 → 720

Every observer gets exactly one step of 60 per turn. Turn 1 runs 0–360 (one cover). Turn 2 runs 360–720 (the mirror cover). At 720 = 0 the matrix rolls over.

A.5 — Closed loop and roll-over

The closed loop is 5 steps (the pentagon). The steps are 5; the operator is 6. The roll-over is 720 (the full macro, double cover closed). The distinction matters: 5 is the loop, 6 is the operator, 720 is the macro roll-over.
§B — Rank 1: the invariants

B.1 — The invariant table
Reading	Rank shift	Invariant	Type
Roll-over	2 → 0	7+3φ7+3φ	metric (Z[φ]Z[φ])
Mirror axis	2 → 1	3+φ3+φ	metric (Z[φ]Z[φ])
Offset	1 → 2	1 (edge count)	structural (ZZ)
Closed loop	1 → 1	order 5	structural (ZZ)

Two metric invariants, two structural invariants. The invariant type follows from the anchor rank: rank-2 readings give metric invariants, rank-1 readings give structural invariants.

B.2 — Verified metric invariants

Roll-over — 7+3φ7+3φ. Antipodal chord from observer O=(0,1,φ)O=(0,1,φ) to vertex Q=(−1,−1,−1)Q=(−1,−1,−1):
v=Q−O=(−1,−2,−1−φ)
v=Q−O=(−1,−2,−1−φ)
⟨v,v⟩=1+4+(1+φ)2=5+(1+2φ+φ2)=7+3φ✓
⟨v,v⟩=1+4+(1+φ)2=5+(1+2φ+φ2)=7+3φ✓

Mirror axis — 3+φ3+φ. Mirror plane x=0x=0 (stated convention; the other five axes are equivalent under II). Observer O=(1,φ,0)O=(1,φ,0), mirror-plane vertex Q=(0,φ−1,φ)Q=(0,φ−1,φ):
v=Q−O=(−1,−1,φ)
v=Q−O=(−1,−1,φ)
⟨v,v⟩=1+1+φ2=3+φ✓
⟨v,v⟩=1+1+φ2=3+φ✓

The other mirror-plane vertex (0,−(φ−1),φ)(0,−(φ−1),φ) gives 7+φ7+φ, so the choice is stated: Q=(0,φ−1,φ)Q=(0,φ−1,φ).

B.3 — The offset invariant: edge count

The offset reading is "the first step from the observation point." It is a graph distance, not a metric distance. The first step is one edge:
offset invariant=1(edge count, Z)
offset invariant=1(edge count, Z)

The 12 icosahedron points are face-center directions, not positions. Converting them to positions requires the scale factor 1+φ21+φ2
​, which is a root and therefore forbidden at rank 1. The edge count avoids the scale factor entirely. The candidate metric values 3−φ3−φ and 5−3φ5−3φ came from treating face-center directions as positions; that is a category error, corrected here.

B.4 — The closed loop: order 5

The closed loop is the 5-step pentagon cycle. It has two exact readings:

Rank 2 (linear sum). The face center is the average of the 5 pentagon vertices, so the chord sum is exactly zero. The pentagon closes. This is the hard zero at rank 2.

Rank 1 (group action). The 5 vertices are permuted by a rotation about the axis through the face center and the opposite face center. That rotation has order 5: five applications return the identity. It is an element of II, and there are 24 such elements (6 axes × 4 non-trivial rotations of order 5).

The loop's invariant is order 5 (in ZZ), not a metric norm. The loop is the rank shift between the two readings: zero at rank 2, order 5 at rank 1. It is the only lezing with two visible exact readings.

B.5 — The four invariants, final
text

Roll-over    : 7 + 3φ      metric, verified
Mirror axis  : 3 + φ       metric, verified (stated vertex choice)
Offset       : 1           structural (edge count)
Closed loop  : order 5     structural (group order)

Two metric in Z[φ]Z[φ], two structural in ZZ. The split follows the anchor rank: rank-2 readings give metric invariants, rank-1 readings give structural invariants. This is not a defect — it is the rank ladder operating as designed.
§C — Rank 2: the four readings as rank shifts
Reading	Shift	From → To
Roll-over	S−2S−2	Rank 2 → Rank 0
Mirror axis	S−1S−1	Rank 2 → Rank 1
Closed loop	S0S0	Rank 1 → Rank 1
Offset	S+1S+1	Rank 1 → Rank 2

Anchor-rank test: anchor_rank(puzzle)+shift(reading)∈{0,1,2}anchor_rank(puzzle)+shift(reading)∈{0,1,2}. All 12 puzzles pass.

The shift group is ZZ acting on the ranks {0,1,2}{0,1,2} by addition. SS is a relabeling, not a computation: the object is identical, only its rank tag changes.
§D — The twelve puzzles
#	Puzzle	Observer (axis, pos)	Reading	Wave mode	Status
3.1	Poincaré	(1, +)	roll-over	5	assigned
3.2	Navier–Stokes	(1, −)	roll-over	3	assigned
3.3	Yang–Mills	(6, −)	offset	3′	assigned
3.4	Riemann	(3, +)	mirror axis	—	unassigned
3.5	BSD	(3, −)	mirror axis	—	unassigned
3.6	Hodge	(4, +)	closed loop	—	unassigned
3.7	P vs NP	(4, −)	closed loop	3	assigned
3.8	Fine structure	(6, +)	offset	3	assigned
3.9	Hierarchy	(2, +)	offset	—	unassigned
3.10	Black hole	(5, +)	closed loop	1	assigned
3.11	Horizon	(5, −)	closed loop	1	assigned
3.12	Time	(2, −)	roll-over	3	assigned

The mapping is a clustering by reading class, not a bijection. Ten observer slots are unused under this assignment.

Reading classes:
text

roll-over   : 3 puzzles
mirror axis : 2 puzzles
closed loop : 4 puzzles
offset      : 3 puzzles

Wave modes: eight assigned, four unassigned

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

Unassigned (argument fails):
text

3.4 Riemann    → unassigned — argument fails (Re(s)=1/2 is not 72°)
3.5 BSD        → unassigned — argument fails (rank is not bounded by 4)
3.6 Hodge      → unassigned — argument fails (cycles are not four-fold)
3.9 Hierarchy  → unassigned — argument fails (10³² has no five-fold structure)

Eight wave modes are assigned with a defensible argument. Four are unassigned because the argument fails. A wrong analogy is worse than an empty slot.
§E — What is structural and what is conjectural

Structural:

    The rank ladder (0 / 1 / 2) and the shift operator SS.

    The anchor-rank test.

    The counting chain (1–5) and the operator (6).

    The four units: 6 (micro), 36 (full micro), 60 (macro step), 720 (full macro), 360 (half-macro).

    The closure (22×3×5=6022×3×5=60) and the rank-shift ladder of the closure (60→3,600→12,960,00060→3,600→12,960,000; exponents doubling; primes 2, 3, 5).

    The positional matrix: 6 axes × 2 turns = 12 observers, double cover.

    The Z[φ]Z[φ] geometry: 12 face-center directions, 20 dodecahedron vertices, exact chord vectors, exact squared norms.

    The verified metric invariants: 7+3φ7+3φ (roll-over), 3+φ3+φ (mirror axis).

    The structural invariants: 1 (offset edge count), order 5 (closed loop).

    The invariant-type split: rank-2 readings → metric; rank-1 readings → structural.

    The observer labels (axis, position).

Conjectural:

    The target assignment (which vertex for which puzzle).

    The observer assignment (a clustering by reading class, not a bijection; ten slots unused).

    The wave modes: eight assigned with a defensible argument, four unassigned because the argument fails.

The paper does not solve the puzzles. It classifies them.
§F — Closing

All four invariants are locked:
text

7 + 3φ    (roll-over)    metric
3 + φ     (mirror axis)  metric
1         (offset)       structural (edge count)
order 5   (closed loop)  structural (group order)

Two are metric, two are structural, and the split follows the anchor rank. There is no pending computation.

The compass is a dodecahedral vector system with 12 face-center observers, exact Z[φ]Z[φ] geometry, a 720-step double-cover macro cycle, and four readings that are rank shifts. The metric readings produce exact squared norms; the structural readings produce exact integer invariants. Base-60 applies only at rank 0. Lengths and roots are never computed; they are read at rank 2.

End of appendix.
