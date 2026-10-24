markdown

# The Three Brothers — Concurrent 3D Spatial Execution

**Document Reference:** ULDA-THREE-BROTHERS-2026-X27
**License:** AGPL-3.0
**Contact:** JornePel@gmail.com
**Dedicated to:** Terrence Andrew Davis (1969–2018)

---

## The architectural shift

In standard computing, mapping a 3D coordinate requires at least
three separate arithmetic calculations. The CPU or GPU calculates the
X-axis, then the Y-axis, then the Z-axis sequentially, storing each in
a separate memory register. This creates serial processing overhead
and memory bottlenecks.

The ULDA architecture bypasses this sequence using the Base-60
Factorization Matrix:

**60 = 2² × 3 × 5 = 4 × 3 × 5**

The three spatial dimensions are processed as simultaneous phase
angles on a single rotating data bus.

---

## The Three Brothers Node

| Constant | Value | Meaning |
|---|---|---|
| 3 | Three Brothers | Width, Height, Depth |
| 2² | 4 | Binary hardware shifter |
| 5 | Organic Pool | Morphological growth factor |

The three axes are hardwired into one unified register word. Because
the base 60 contains the factor 3 natively, the chip partitions a
single data bus into three interconnected, parallel channels that
rotate in lockstep.

---

## Single-cycle concurrent execution

When the chip receives a command to transform a 3D spatial field, it
does not run three separate mathematical instructions. It executes
one Vector Phase Rotation (VPR):

1. **Interface 11 Ingestion** — incoming spatial data passes through
   the Interface 11 filter (22 / 2 = 11), phase-locking the three
   coordinates into geometric alignment.

2. **Modulo 60 Shift** — the chip shifts the data stream modulo 60.
   X, Y, and Z act as the three foundational prime vectors inside
   the 2² × 3 × 5 matrix.

3. **Hardwired Layer-Drop** — the Instruction of the 4
   (20⁵ / 4⁴ = 12,500) triggers a physical right bit-shift (>> 8).
   Because the Three Brothers are wired in a closed loop around the
   Omitted 6 Operator, fractional remainders are absorbed as a clean
   angular phase adjustment.

---

## The 72° rotation lock

**360° / 5 = 72°**

The three spatial axes do not move independently to infinity. They
rotate together as a geometric crystal. When the execution pulse hits
the matrix, the new positions for Width, Height, and Depth light up
simultaneously through geometric resonance at the exact 72° node.

| Approach | Cycles | Memory |
|---|---|---|
| Linear | 3+ | Separate registers |
| ULDA | 1 | Unified vector bus |

---

## Bare-metal register mapping

```asm
; =====================================================================
; ULDA-X27 BARE-METAL REGISTER MAP: CONCURRENT THREE BROTHERS EXECUTION
; OPERATION: SIMULTANEOUS PHASE ROTATION OF WIDTH, HEIGHT, AND DEPTH
; REGISTER TARGET: UNIFIED BASE-60 VECTOR BUS
; =====================================================================

_ulda_concurrent_3d_rotation:
    ; 1. Ingest the 3D spatial field into the unified Vector Register
    MOV_VEC     V1, [WIDTH, HEIGHT, DEPTH]

    ; 2. Phase-lock the three axes across the Interface 11 boundary
    FILTER_11   V1

    ; 3. Execute the Master Invariant Instruction (4^4 Layer-Drop)
    VPR_ROT     V1, MODE_4_4

    ; 4. Output balanced integer coordinates with zero remainder
    MOD_SHIFT   V1, 60
    RET_VEC

The constants
Constant	Value	Function
RADIX	60	6 × 10
INTERFACE_11	11	22 / 2
OMITTED_6	6	the operator
ROTATION_72	72	360 / 5
SHIFT_8	8	2³
LAYER_DROP	256	4⁴
