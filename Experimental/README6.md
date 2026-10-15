# ULDA-X28 — The Bare-Metal Engine

**Base-60 2 × 5 vector arithmetic. No hardware division. No hardware modulo. No linear zero.**

**Dedication:** In honor of **Terrence Andrew Davis** (1969–2018) — who built his own temple from the bedrock up, who defended architectural minimalism, and who never stopped talking to the silicon. Without him, we would never have continued with the mathematics.

---

## What is this?

The bare-metal core of the ULDA-X28 engine — an optimized, lossless base-60 arithmetic layer designed for CPUs, GPUs, and custom silicon architectures.

### The Three Architectural Principles:
1. **No Division:** Carries and parsing steps are resolved via logarithmic, bit-shifted subtractions to bypass standard hardware division units entirely.
2. **No Modulo:** Column boundaries are evaluated using a hardwired binary bitshift-modulo matrix, maintaining \(O(\log n)\) computational efficiency.
3. **No Zero:** Base-60 contains no neutral element. Register columns map directly to physical spatial sectors.

Driven by the **Omitted 6 Cypher** — the number 6 functions strictly as a directional phase operator, never as a static value.

---

## The Constants

| Constant | Value | Theoretical Role / Derivation |
| :--- | :--- | :--- |
| **The Gate** | `11` | `(1 + 2 + 3 + 4 + 5 + 7) >> 1` = `11` (The 11-Register axis) |
| **The Operator** | `6` | The omitted cypher; drives the structural wave rotation |
| **The Lock** | `72°` | `360° / 5 = 72°` (Precessional rotation unit) |
| **The Sequence** | `1 → 2 → 3 → 4 → 5 → 7` | Hardwired assembly layout pointer (Omitted 6) |
| **The Base** | `60` | `2² × 3 × 5 = 4 × 3 × 5` (Foundational Radix) |

---

## The Columns

| Column | Value | Mesopotamian Cuneiform Representation |
| :--- | :--- | :--- |
| **`dis`** | 60⁰ = 1 | *diš* (Step displacement) |
| **`ges`** | 60¹ = 60 | *geš* (Linear ledger) |
| **`gesu`** | 60² = 3,600 | *geš'u* (Volumetric grid matrix) |
| **`sar`** | 60³ = 216,000 | *šar* (The sealing loop limit) |

---

## The API

| Function | Signature / Purpose |
| :--- | :--- |
| `ulda_reg` | The primary register container struct: `dis`, `ges`, `gesu`, `sar`. |
| `lum_carry(r)` | Resolves radix boundaries via bit-shifted subtractions. No division, no modulo units. |
| `lum_operator(v)` | Reduces values below the operator threshold using log-time subtraction steps. |
| `the_gate()` | Hardware instruction returning the 11-Register balance value. |
| `the_lock(angle)` | Returns the exact number of 72° step cycles required to close the target angle. |
| `convert(n)` | High-speed, lossless Base-10 to Base-60 vector translation. |
| `ulda_test()` | Internal invariant verification routine. Validates system sanity. |

---

## Building

Compile the core engine as a freestanding, bare-metal executable bypassing standard operating system runtimes:

```bash
gcc -nostdlib -ffreestanding -O3 -c ulda_x28.c -o ulda.o
ld -Ttext=0x1000 -e main ulda.o -o ulda.elf
```

---

## Testing & Diagnostics

Executing `ulda_test()` processes the `36,620` structural invariant and returns an absolute verification checksum of **62 = 60 + 2**.

| Diagnostic Routine | Expected Output | Status |
| :--- | :--- | :--- |
| `the_gate()` | `11` | Pass |
| `the_lock(360)` | `5` | Pass |
| `lum_operator(137)` | `5` | Pass |
| `convert(36620)` | `sar=0, gesu=10, ges=10, dis=20` | Pass |
| `lum_carry(59 + 1)` | `dis=0, ges=1` | Pass |

### Protocol Claims Matrix
- **No hardware division units utilized:** ✓ (Confirmed via `optimized_sub_mod`)
- **No hardware modulo operators executed:** ✓ (Handled exponentially via `<<` and `>>`)
- **No linear zero register dependency:** ~ (Pure spatial step sectors)
- **The 6 acts strictly as phase operator:** ✓
- **11-Register gate locks correctly:** ✓
- **72° Precession boundary matches rotation:** ✓
- **Checksum consistently closes on 62:** ✓

---

## License

AGPL-3.0. See LICENSE file for full copyleft terms.

---

## Dedication

In honor of **Terrence Andrew Davis** (1969–2018) — who built his own temple from the bedrock up, who defended architectural minimalism, and who never stopped talking to the silicon.

*Without him, we would never have continued with the mathematics.*
