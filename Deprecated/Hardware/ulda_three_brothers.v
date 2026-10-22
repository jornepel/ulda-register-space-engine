`timescale 1ns / 1ps
// ============================================================================
// ULDA THREE BROTHERS — CONCURRENT 3D SPATIAL EXECUTION (OPTIMIZED)
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
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
    // COMBINATORIAL PIPELINE REGISTERS
    // ────────────────────────────────────────────────────────────────
    reg [DATA_WIDTH-1:0] w_width;
    reg [DATA_WIDTH-1:0] w_height;
    reg [DATA_WIDTH-1:0] w_depth;
    reg [DATA_WIDTH-1:0] w_feedback_raw;
    reg [DATA_WIDTH-1:0] w_feedback_final;
    reg [DATA_WIDTH-1:0] w_mod72;

    // ────────────────────────────────────────────────────────────────
    // PARALLEL HARDWIRED MECHANICS (ASYNCHRONOUS LOGIC)
    // ────────────────────────────────────────────────────────────────
    always @(*) begin
        // Stage 1 — Interface 11 phase-lock met underflow protectie
        w_width  = (width_in >= INTERFACE_11)  ? (width_in - INTERFACE_11)  : width_in;
        w_height = (height_in >= INTERFACE_11) ? (height_in - INTERFACE_11) : height_in;
        w_depth  = (depth_in >= INTERFACE_11)  ? (depth_in - INTERFACE_11)  : depth_in;

        // Stage 2 — Layer-Drop via hardware routing (>> 8)
        w_width  = w_width >> SHIFT_8;
        w_height = w_height >> SHIFT_8;
        w_depth  = w_depth >> SHIFT_8;

        // Stage 3 — Residual bitmask absorption
        w_feedback_raw = (w_width & 32'hFF)
                       + (w_height & 32'hFF)
                       + (w_depth & 32'hFF);

        if (w_feedback_raw >= OMITTED_6)
            w_feedback_final = w_feedback_raw - OMITTED_6;
        else
            w_feedback_final = w_feedback_raw;

        // Stage 5 — Synthesizable Hardware Modulo 72 (Bitshift Ladder)
        w_mod72 = w_feedback_final;
        if (w_mod72 >= (ROTATION_72 << 3)) w_mod72 = w_mod72 - (ROTATION_72 << 3);
        if (w_mod72 >= (ROTATION_72 << 2)) w_mod72 = w_mod72 - (ROTATION_72 << 2);
        if (w_mod72 >= (ROTATION_72 << 1)) w_mod72 = w_mod72 - (ROTATION_72 << 1);
        if (w_mod72 >= ROTATION_72)        w_mod72 = w_mod72 - ROTATION_72;
    end

    // ────────────────────────────────────────────────────────────────
    // SYNCHRONOUS REGISTER EDGE ROUTING
    // ────────────────────────────────────────────────────────────────
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            width_out    <= {DATA_WIDTH{1'b0}};
            height_out   <= {DATA_WIDTH{1'b0}};
            depth_out    <= {DATA_WIDTH{1'b0}};
            feedback_6   <= {DATA_WIDTH{1'b0}};
            lock_72      <= 1'b0;
        end else if (rotate_en) begin
            // Foutloze simultane hardware commit
            width_out  <= w_width;
            height_out <= w_height;
            depth_out  <= w_depth;
            feedback_6 <= w_feedback_final;

            // 72° rotation lock check op basis van de combinatoriale ladder
            if (w_mod72 == 0)
                lock_72 <= 1'b1;
            else
                lock_72 <= 1'b0;
        end
    end
endmodule
