# ULDA — Topological Decoder Engine

A C implementation of the exact ℤ[φ] arithmetic and four invariants described
in *The Compass and the Twelve Puzzles* (Jorne Pel, 2026).

**The paper is the specification. This engine is the proof.**

---

## What this is

A small, exact, dependency-free C engine that computes the four invariants of
the compass geometry in ℤ[φ]³ — the ring of numbers of the form `a + bφ` where
φ² = φ + 1. No floating point. No roots. No rounding.

It is used two ways:

1. **Standalone** — `./test` verifies the four invariants against §8 of the paper.
2. **As a library** — `libulda.so` / `libulda.dylib`, callable from Python via
   `ctypes`, driving the 8-rib protocol in `ulda_grid.py`.

---

## The four invariants

| Reading       | Rank shift | Invariant   | Type              |
|---------------|------------|-------------|-------------------|
| Roll-over     | 2 → 0      | `7 + 3φ`    | metric (ℤ[φ])     |
| Mirror axis   | 2 → 1      | `3 + φ`     | metric (ℤ[φ])     |
| Offset        | 1 → 2      | `1`         | structural (ℤ)    |
| Closed loop   | 1 → 1      | `order 5`   | structural (ℤ)    |

Two metric, two structural. The split follows the anchor rank.

---

## Files

ulda.h The engine header. ℤ[φ] arithmetic, vector ops, invariant contracts.
ulda.c The implementation. Asserts the metric invariants; returns the
structural constants.
ulda_shim.c Flat C interface for ctypes. Exposes chord_sqnorm_flat.
puzzles.h The 12 puzzles, 20 vertices, 12 observers — as data.
puzzles.c The tables.
test.c Invariant test harness. ./test must pass.
bench.c Hot-path benchmark. Measures chord_sqnorm_vec and invariant_rollover.
demo.c Demonstration walk-through of the compass.
ulda_grid.py The 8-rib protocol. Calls the C engine via ctypes.
Makefile Builds everything. make lib produces the shared library.
run_tests.sh Full pipeline: build, test, benchmark, Python cross-check, demo.
text


---

## Build

Requires a C compiler (`cc`) and `make`. On Windows, install MSYS2 and use the
**MINGW64** terminal — `pacman -S make mingw-w64-x86_64-gcc`.

### Everything

```bash
make clean
make test
make bench
make demo
make lib

Just the executables
bash

make test
make bench
make demo

Just the shared library (for Python)
bash

make lib

Produces libulda.so on Linux, libulda.dylib on macOS, libulda.so on
MSYS2/Windows.
Run
C test — verify the four invariants
bash

./test

Expected:
text

roll-over : 7 + 3φ  (expect 7 + 3φ)
mirror    : 3 + 1φ  (expect 3 + φ)
offset    : 1  (expect 1)
loop      : 5  (expect 5)
...
all invariants check out

C benchmark
bash

./bench

Prints ns/call for chord_sqnorm_vec and invariant_rollover (best of 5 reps).
C demo
bash

./demo

Walks the 20 vertices, 12 observers, 240 chords, 4 invariants, 12 puzzles, and
the scope boundary.
Python protocol (calls the C engine via ctypes)
bash

ULDA_BACKEND=stub python3 ulda_grid.py

Expected: the 8-rib chain runs on the rollover chord, the arithmetic veto
confirms 7 + 3φ == 7 + 3φ, the claim survives with status ✓.

The key output line:
json

"computed": "7 + 3φ",
"expected": "7 + 3φ"

That value came from C, through ctypes, into Python.
Full pipeline
bash

chmod +x run_tests.sh
./run_tests.sh

Runs all six stages. Ends with 🔥 PIPELINE COMPLETE.
The 8-rib protocol (ulda_grid.py)

The Python script implements a single-agent grading protocol on top of the
engine:

    8 rib gates — one per cube vertex (±1,±1,±1). Each gate says ✓, ~,
    ?, or ✗. Any ✗ kills the chain; later gates are not asked.

    1 arithmetic veto — after all 8 gates pass, the C engine computes
    chord_sqnorm(Q − O) and compares to the reading's expected invariant.
    Mismatch → claim dies (recorded as killed_at: 9).

    Final status — min over the 8 gates, order ✗ < ? < ~ < ✓. A single ?
    keeps the claim at ?; a single ~ downgrades to ~; all ✓ → ✓.

    Death reasoning — every killed claim gets a gate-by-gate reasoning list
    and a conclusion derived from the chain. Queryable in audit().

Three backends:
bash

ULDA_BACKEND=stub      python3 ulda_grid.py    # deterministic, for CI
ULDA_BACKEND=openai    python3 ulda_grid.py    # requires OPENAI_API_KEY
ULDA_BACKEND=anthropic python3 ulda_grid.py    # requires ANTHROPIC_API_KEY

Verification paths

The protocol's behaviour is verified end-to-end. All paths must pass:
Path	Test
Survivor (all ✓, veto passes)	ULDA_BACKEND=stub → status ✓
Rib rejection (a gate says ✗)	Edit stub gate to ✗ → killed_at: N
Arithmetic veto (wrong chord)	Edit stub Q → killed_at: 9

The C test and the Python protocol use the same fixture (the rollover
chord from test.c). If both print 7 + 3φ, the engine and the protocol agree.
Why ℤ[φ]

All coordinates are exact in the ring ℤ[φ]. No root is taken; no decimal
appears. The only irrationality is deferred to rank 2, where it is read,
not evaluated.

This is the paper's central arithmetic claim, and it is what makes the engine's
invariants checkable by == rather than by tolerance.
The specification

This engine implements the arithmetic and geometry of:

    The Compass and the Twelve Puzzles
    Jorne Pel, 2026.

The paper defines the four invariants (§10), the geometry (§6–§7), the observer
labels (§4.4), the rank-shift operator (§5), and the assignment of the 12
puzzles to readings (§11). The engine's PUZZLES[12] table is that assignment,
made executable.

The paper's changelog and correction log document every grade revision. The
engine's test.c verifies the four graded invariants. If they disagree, one
of them is wrong.
License

Copyright (c) 2026 Jorne Pel. All rights reserved.

As above, so below. And if there is a difference, that is friction, not error.
text


---

## Notes on the README

- **"The paper is the specification. This engine is the proof."** — that's the sentence the whole thing hangs on. If someone opens the folder and reads only one line, that's it.
- **The verification paths table** — three rows, each one a test that must pass. This is what makes the README trustworthy: it says *what you can check*, not just *what the code does*.
- **The "Why ℤ[φ]" section** — one paragraph, but it's the whole point of the exact arithmetic. Someone who doesn't know the paper will read this and understand why the engine doesn't use floats.
- **The specification section** — points at the paper, names the sections the engine implements, and ends with *"If they disagree, one of them is wrong."* That's the discipline you've been applying all along, stated in the README itself.

Save it as `README.md` in the engine folder, next to `MANIFESTO.md` and `PAPER.md`. Then:

```bash
git add README.md
git commit -m "Add engine README: spec + build + verification paths"