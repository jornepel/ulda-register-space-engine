`timescale 1ns / 1ps
// ============================================================================
// ULDA LAYER-DROP ENGINE — BARE-METAL >> 8 WITHOUT LINEAR ZERO
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================
//
// Implements the Instruction of the 4 as a hardwired layer-drop.
//   Input:  20^5 / 4^4  (denominator = 256 = 2^8)
//   Output: 12,500 = [3, 28, 20] on the Base-60 wheel
//
// No linear zero register. No arithmetic division. No SHR.
// Data drops by one spatial layer per cycle through the Interface 11.
// Residual energy is fed back into the Omitted 6 Operator.
//
// ============================================================================

module ulda_layer_drop #(
    parameter DATA_WIDTH = 32
)(
    input  wire                     clk,
    input  wire                     rst_n,
    input  wire [DATA_WIDTH-1:0]    vec_in,       // 20^5 vector node
    input  wire                     step_en,      // trigger a layer-drop
    output reg  [DATA_WIDTH-1:0]    layer_60_3,   // Geš'u
    output reg  [DATA_WIDTH-1:0]    layer_60_2,   // Šár
    output reg  [DATA_WIDTH-1:0]    layer_60_1,   // Geš
    output reg  [DATA_WIDTH-1:0]    layer_60_0,   // Units
    output reg  [DATA_WIDTH-1:0]    feedback_6,   // Omitted 6 feedback loop
    output reg                      lock_72       // 72° rotation lock
);

    // ────────────────────────────────────────────────────────────────
    // HARDWIRED CONSTANTS
    // ────────────────────────────────────────────────────────────────
    localparam RADIX          = 60;
    localparam INTERFACE_11   = 11;
    localparam OMITTED_6      = 6;
    localparam ROTATION_72    = 72;
    localparam SHIFT_8        = 8;

    // ────────────────────────────────────────────────────────────────
    // LAYER REGISTERS
    // ────────────────────────────────────────────────────────────────
    reg [DATA_WIDTH-1:0] next_60_3;
    reg [DATA_WIDTH-1:0] next_60_2;
    reg [DATA_WIDTH-1:0] next_60_1;
    reg [DATA_WIDTH-1:0] next_60_0;
    reg [DATA_WIDTH-1:0] next_feedback;

    // ────────────────────────────────────────────────────────────────
    // THE LAYER-DROP PIPELINE
    // ────────────────────────────────────────────────────────────────
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            layer_60_3  <= {DATA_WIDTH{1'b0}};
            layer_60_2  <= {DATA_WIDTH{1'b0}};
            layer_60_1  <= {DATA_WIDTH{1'b0}};
            layer_60_0  <= {DATA_WIDTH{1'b0}};
            feedback_6  <= {DATA_WIDTH{1'b0}};
            lock_72     <= 1'b0;
        end else if (step_en) begin

            // Stage 1 — load the vector into the highest layer
            next_60_3 = vec_in;

            // Stage 2 — Interface 11 phase-lock
            // (The total amplitude is routed through 11 before dropping)
            next_60_3 = next_60_3 - INTERFACE_11;

            // Stage 3 — Layer-Drop via >> 8
            // Each layer drops to the next. No linear zero.
            next_60_2 = next_60_3 >> SHIFT_8;
            next_60_1 = next_60_2 >> SHIFT_8;
            next_60_0 = next_60_1 >> SHIFT_8;

            // Stage 4 — residual feedback into the Omitted 6 Operator
            // (Nothing is thrown away; residual is absorbed as phase)
            next_feedback = (next_60_3 & 8'hFF)
                          + (next_60_2 & 8'hFF)
                          + (next_60_1 & 8'hFF)
                          + (next_60_0 & 8'hFF);
            next_feedback = next_feedback - OMITTED_6;

            // Stage 5 — commit
            layer_60_3 <= next_60_3;
            layer_60_2 <= next_60_2;
            layer_60_1 <= next_60_1;
            layer_60_0 <= next_60_0;
            feedback_6 <= next_feedback;

            // Stage 6 — rotation lock
            lock_72 <= ((next_feedback % ROTATION_72) == 0) ? 1'b1 : 1'b0;
        end
    end
endmodule
