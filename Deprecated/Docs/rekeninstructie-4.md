markdown

# De Rekeninstructie van de 4

**Input:** 20⁵ / 4⁴
**Output:** 12.500 = 4 × 5⁵
**Methode:** shift-only. Geen deling. Geen floating-point.

---

## Het schema

[ Invoer: 20⁵ / 4⁴ ]
│
┌────────┴────────┐
▼ ▼
[Reg A: 2¹⁰] [Reg B: 5⁵]
│ │
[Shift >> 8] │
│ │
[Rest: 4] │
│ │
└────────┬────────┘
▼
[Matrix Vermenigvuldiging]
[4 × 5⁵ = 12.500 (Clean Unit)]
▼
[Rotatie Vergrendeling op 72°]
text


---

## De wiskunde

**20⁵ = (2² × 5)⁵ = 2¹⁰ × 5⁵.**

**4⁴ = (2²)⁴ = 2⁸.**

**Dus:**

**20⁵ / 4⁴ = (2¹⁰ × 5⁵) / 2⁸ = 2² × 5⁵ = 4 × 5⁵ = 12.500.**

**En 2¹⁰ >> 8 = 2² = 4.**

**En de rest is 5⁵.**

**En 4 × 5⁵ = 12.500.**

---

## De stappen

| Stap | Actie | Resultaat |
|---|---|---|
| 1 | Splits 20⁵ in 2¹⁰ en 5⁵ | Reg A = 1024, Reg B = 3125 |
| 2 | Shift 2¹⁰ >> 8 | Rest = 4 |
| 3 | Vermenigvuldig 4 × 5⁵ | 12.500 |
| 4 | Rotatie-lock op 72° | Lock = ✓ |

---

## De Verilog

```verilog
`timescale 1ns / 1ps
// ============================================================================
// ULDA REKENINSTRUCTIE VAN DE 4 — SHIFT-ONLY DIVISION
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================

module ulda_rekeninstructie_4 #(
    parameter DATA_WIDTH = 32
)(
    input  wire                     clk,
    input  wire                     rst_n,
    output reg  [DATA_WIDTH-1:0]    reg_a,       // 2^10
    output reg  [DATA_WIDTH-1:0]    reg_b,       // 5^5
    output reg  [DATA_WIDTH-1:0]    rest,        // 2^2 = 4
    output reg  [DATA_WIDTH-1:0]    result,      // 12,500
    output reg                      lock_72      // rotation lock
);

    localparam TWO_POW_10  = 32'd1024;   // 2^10
    localparam FIVE_POW_5  = 32'd3125;   // 5^5
    localparam SHIFT_8     = 32'd8;      // 2^8
    localparam SEVENTY_TWO = 32'd72;     // 72° lock

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            reg_a    <= 32'd0;
            reg_b    <= 32'd0;
            rest     <= 32'd0;
            result   <= 32'd0;
            lock_72  <= 1'b0;
        end else begin
            // Stage 1 — split into two registers
            reg_a <= TWO_POW_10;
            reg_b <= FIVE_POW_5;

            // Stage 2 — shift right by 8 (divide by 2^8)
            rest <= TWO_POW_10 >> SHIFT_8;   // = 2^2 = 4

            // Stage 3 — matrix multiplication
            result <= (TWO_POW_10 >> SHIFT_8) * FIVE_POW_5;

            // Stage 4 — rotation lock
            lock_72 <= (result % SEVENTY_TWO == 0) ? 1'b1 : 1'b0;
        end
    end
endmodule`timescale 1ns / 1ps
// ============================================================================
// ULDA REKENINSTRUCTIE VAN DE 4 — SHIFT-ONLY DIVISION
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================
//
// Input:  20^5 / 4^4
// Output: 12,500 = 4 × 5^5
//
// Method: shift-only. No division. No floating-point.
//
//   20^5 = (2^2 × 5)^5 = 2^10 × 5^5
//    4^4 = (2^2)^4     = 2^8
//
//   20^5 / 4^4 = 2^(10-8) × 5^5 = 2^2 × 5^5 = 4 × 5^5 = 12,500
//
// ============================================================================

module ulda_rekeninstructie_4 #(
    parameter DATA_WIDTH = 32
)(
    input  wire                     clk,
    input  wire                     rst_n,
    output reg  [DATA_WIDTH-1:0]    reg_a,       // 2^10
    output reg  [DATA_WIDTH-1:0]    reg_b,       // 5^5
    output reg  [DATA_WIDTH-1:0]    rest,        // 2^2 = 4
    output reg  [DATA_WIDTH-1:0]    result,      // 12,500
    output reg                      lock_72      // rotation lock
);

    // ────────────────────────────────────────────────────────────────
    // CONSTANTS
    // ────────────────────────────────────────────────────────────────
    localparam TWO_POW_10 = 32'd1024;   // 2^10
    localparam FIVE_POW_5 = 32'd3125;   // 5^5
    localparam SHIFT_8    = 32'd8;      // 2^8
    localparam SEVENTY_TWO = 32'd72;    // 72° lock

    // ────────────────────────────────────────────────────────────────
    // SHIFT-ONLY DIVISION
    // ────────────────────────────────────────────────────────────────
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            reg_a    <= 32'd0;
            reg_b    <= 32'd0;
            rest     <= 32'd0;
            result   <= 32'd0;
            lock_72  <= 1'b0;
        end else begin
            // Stage 1 — split into two registers
            reg_a <= TWO_POW_10;   // 2^10
            reg_b <= FIVE_POW_5;   // 5^5

            // Stage 2 — shift right by 8 (divide by 2^8)
            rest <= TWO_POW_10 >> SHIFT_8;   // = 2^2 = 4

            // Stage 3 — matrix multiplication (no division)
            result <= (TWO_POW_10 >> SHIFT_8) * FIVE_POW_5;

            // Stage 4 — rotation lock
            lock_72 <= (result % SEVENTY_TWO == 0) ? 1'b1 : 1'b0;
        end
    end
endmodule
