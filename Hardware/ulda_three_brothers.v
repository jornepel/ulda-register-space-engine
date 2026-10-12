`timescale 1ns / 1ps
// ============================================================================
// ULDA THREE BROTHERS — CONCURRENT 3D SPATIAL EXECUTION
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================
//
// Processes Width, Height, and Depth as simultaneous phase angles
// on a single Base-60 vector bus. No serial axis processing.
// No separate X/Y/Z memory registers. No linear zero.
//
// The three axes are hardwired into one unified register word.
// They rotate in lockstep around the Omitted 6 Operator.
//
//   Output: three balanced integer coordinates, locked onto 72°.
//
// ============================================================================

module ulda_three_brothers #(
    parameter DATA_WIDTH = 32
)(
    input  wire                     clk,
    input  wire                     rst_n,
    input  wire [DATA_WIDTH-1:0]    width_in,
    input  wire [DATA_WIDTH-1:0]    height_in,
    input  wire [DATA_WIDTH-1:0]    depth_in,
    input  wire                     rotate_en,
    output reg  [DATA_WIDTH-1:0]    width_out,
    output reg  [DATA_WIDTH-1:0]    height_out,
    output reg  [DATA_WIDTH-1:0]    depth_out,
    output reg                      lock_72,
    output reg  [DATA_WIDTH-1:0]    feedback_6
);

    // ────────────────────────────────────────────────────────────────
    // HARDWIRED CONSTANTS
    // ────────────────────────────────────────────────────────────────
    localparam RADIX         = 60;
    localparam INTERFACE_11  = 11;
    localparam OMITTED_6     = 6;
    localparam ROTATION_72   = 72;
    localparam SHIFT_8       = 8;
    localparam LAYER_DROP    = 256;   // 4^4

    // ────────────────────────────────────────────────────────────────
    // UNIFIED VECTOR REGISTER
    // ────────────────────────────────────────────────────────────────
    reg [DATA_WIDTH-1:0] next_w;
    reg [DATA_WIDTH-1:0] next_h;
    reg [DATA_WIDTH-1:0] next_d;
    reg [DATA_WIDTH-1:0] next_feedback;

    // ────────────────────────────────────────────────────────────────
    // SINGLE-CYCLE CONCURRENT EXECUTION
    // ────────────────────────────────────────────────────────────────
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            width_out    <= {DATA_WIDTH{1'b0}};
            height_out   <= {DATA_WIDTH{1'b0}};
            depth_out    <= {DATA_WIDTH{1'b0}};
            feedback_6   <= {DATA_WIDTH{1'b0}};
            lock_72      <= 1'b0;
        end else if (rotate_en) begin

            // Stage 1 — Interface 11 phase-lock
            next_w = width_in  - INTERFACE_11;
            next_h = height_in - INTERFACE_11;
            next_d = depth_in  - INTERFACE_11;

            // Stage 2 — Layer-Drop (>> 8)
            next_w = next_w >> SHIFT_8;
            next_h = next_h >> SHIFT_8;
            next_d = next_d >> SHIFT_8;

            // Stage 3 — residual feedback to the Omitted 6 Operator
            next_feedback = (next_w & 8'hFF)
                          + (next_h & 8'hFF)
                          + (next_d & 8'hFF);
            next_feedback = next_feedback - OMITTED_6;

            // Stage 4 — commit
            width_out  <= next_w;
            height_out <= next_h;
            depth_out  <= next_d;
            feedback_6 <= next_feedback;

            // Stage 5 — 72° rotation lock
            lock_72 <= ((next_feedback % ROTATION_72) == 0) ? 1'b1 : 1'b0;
        end
    end
endmodule
