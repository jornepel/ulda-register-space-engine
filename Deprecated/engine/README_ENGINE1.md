# ULDA Engine 1 — Quantum Decoder

**Role:** The core systolic decoder. Verilog + Python reference.

**Target:** Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays.

**License:** AGPL-3.0.

**Dedication:** Terrence Andrew Davis (1969–2018).

---

## What it does

The engine implements a fixed-point sexagesimal carry logic with three stages:

1. **Stage 1** — compute the raw sums (`next_dis`, `next_ges`, `next_sar`).
2. **Stage 2** — resolve carries from the computed sums.
3. **Stage 3** — commit to the registers.

No floating-point. No `//` or `%`. No radix-drift.

---

## Files

| File | Language | Role |
|---|---|---|
| `ulda_systolic_core.v` | Verilog | The core module |
| `ulda_register.py` | Python | The `AdvancedCrossBaseRegister64` reference |
| `tb_ulda.v` | Verilog | Testbench (carry chain, 3 tests) |
| `ulda_systolic_core_tb.v` | Verilog | Testbench (Port-11 interface) |
| `synth.tcl` | Tcl | Vivado synthesis script |

---

## The Hardwired Constants

| Constant | Value | Meaning |
|---|---|---|
| RADIX | 60 | 6 × 10 |
| MASK_CELL | 2¹⁸ − 1 | 18-bit bit-slice |
| ENVELOPE_216 | 216 | 6³ |
| BOUNDARY_504 | 504 | 7 × 72 |
| LADDER_36 | 36 | 6² |
| PRECESSION_72 | 72 | precession unit |
| BRANCH_7 | 7 | post-divider branches |

---

## Usage

### Python

```bash
python ulda_register.py

FPGA Synthesis
bash

vivado -mode batch -source synth.tcl

The Carry Logic
text

Stage 1: next_dis = internal_dis + dis_in
         next_ges = internal_ges + ges_in
         next_sar = internal_sar + sar_in

Stage 2: if next_dis >= 60:
             next_dis -= 60
             next_ges += 1
         if next_ges >= 60:
             next_ges -= 60
             next_sar += 1

Stage 3: internal_dis <= next_dis
         internal_ges <= next_ges
         internal_sar <= next_sar

The Port-11 Test
text

Inject 11 → DIS = 11, GES = 0, SAR = 0
Inject 49 → 11 + 49 = 60 → carry → DIS = 0, GES = 1, SAR = 0
Check: ges_out == 1 && dis_out == 0 → SUCCESS

The Carry Chain Test
text

Test 1: 60 × dis_in = 1 → DIS = 0, GES = 1, SAR = 0
Test 2: 60 × ges_in = 1 → DIS = 0, GES = 0, SAR = 1
Test 3: carry chain dis → ges → sar

Dedication

To Terrence Andrew Davis (1969–2018).

"A computer scientist who defended architectural minimalism, the integrity of native binary execution, and the elimination of systemic computational complexity."
