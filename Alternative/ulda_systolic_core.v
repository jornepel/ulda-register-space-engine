`timescale 1ns / 1ps
// ============================================================================
// ULDA SYNTHESIZABLE SYSTOLIC DECODER NODE CORE (COMPILER OPTIMIZED)
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================

module ulda_systolic_core #(
    parameter DATA_WIDTH = 18
)(
    input  wire                   clk,
    input  wire                   rst_n,
    input  wire [DATA_WIDTH-1:0]  dis_in,
    input  wire [DATA_WIDTH-1:0]  ges_in,
    input  wire [DATA_WIDTH-1:0]  sar_in,
    output reg  [DATA_WIDTH-1:0]  dis_out,
    output reg  [DATA_WIDTH-1:0]  ges_out,
    output reg  [DATA_WIDTH-1:0]  sar_out
);

    // Physical state registers
    reg [DATA_WIDTH-1:0] internal_dis;
    reg [DATA_WIDTH-1:0] internal_ges;
    reg [DATA_WIDTH-1:0] internal_sar;

    // Combinatorial wire networks (FIXED: Moved out of the sequential clock block)
    reg [DATA_WIDTH-1:0] w_next_dis;
    reg [DATA_WIDTH-1:0] w_next_ges;
    reg [DATA_WIDTH-1:0] w_next_sar;
    
    reg [DATA_WIDTH-1:0] w_dis_carry;
    reg [DATA_WIDTH-1:0] w_ges_carry;

    // ────────────────────────────────────────────────────────────────
    // ASYNCHRONOUS BITSHIFT-CARRY PIPELINE (LOGARITHMIC RESOLUTION)
    // ────────────────────────────────────────────────────────────────
    always @(*) begin
        // Raw concurrent matrix accumulation sums
        w_next_dis = internal_dis + dis_in;
        w_next_ges = internal_ges + ges_in;
        w_next_sar = internal_sar + sar_in;

        // Vectorized, synthesizable Modulo-60 carry ladder for DIS -> GES
        w_dis_carry = {DATA_WIDTH{1'b0}};
        if (w_next_dis >= (18'd60 << 2)) begin w_next_dis = w_next_dis - (18'd60 << 2); w_dis_carry = w_dis_carry + (18'd1 << 2); end
        if (w_next_dis >= (18'd60 << 1)) begin w_next_dis = w_next_dis - (18'd60 << 1); w_dis_carry = w_dis_carry + (18'd1 << 1); end
        if (w_next_dis >= 18'd60)        begin w_next_dis = w_next_dis - 18'd60;        w_dis_carry = w_dis_carry + 18'd1;        end
        
        w_next_ges = w_next_ges + w_dis_carry;

        // Vectorized, synthesizable Modulo-60 carry ladder for GES -> SAR
        w_ges_carry = {DATA_WIDTH{1'b0}};
        if (w_next_ges >= (18'd60 << 2)) begin w_next_ges = w_next_ges - (18'd60 << 2); w_ges_carry = w_ges_carry + (18'd1 << 2); end
        if (w_next_ges >= (18'd60 << 1)) begin w_next_ges = w_next_ges - (18'd60 << 1); w_ges_carry = w_ges_carry + (18'd1 << 1); end
        if (w_next_ges >= 18'd60)        begin w_next_ges = w_next_ges - 18'd60;        w_ges_carry = w_ges_carry + 18'd1;        end
        
        w_next_sar = w_next_sar + w_ges_carry;
    end

    // ────────────────────────────────────────────────────────────────
    // SYNCHRONOUS HARDWARE FLIP-FLOP COMMIT
    // ────────────────────────────────────────────────────────────────
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            internal_dis <= {DATA_WIDTH{1'b0}};
            internal_ges <= {DATA_WIDTH{1'b0}};
            internal_sar <= {DATA_WIDTH{1'b0}};
            dis_out      <= {DATA_WIDTH{1'b0}};
            ges_out      <= {DATA_WIDTH{1'b0}};
            sar_out      <= {DATA_WIDTH{1'b0}};
        end else begin
            // Clean non-blocking commitments to physical logic blocks
            internal_dis <= w_next_dis;
            internal_ges <= w_next_ges;
            internal_sar <= w_next_sar;

            dis_out      <= w_next_dis;
            ges_out      <= w_next_ges;
            sar_out      <= w_next_sar;
        end
    end
endmodule
