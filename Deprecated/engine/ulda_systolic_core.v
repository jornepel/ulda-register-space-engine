`timescale 1ns / 1ps
// ============================================================================
// ULDA SYNTHESIZABLE SYSTOLIC DECODER NODE CORE
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

    reg [DATA_WIDTH-1:0] internal_dis;
    reg [DATA_WIDTH-1:0] internal_ges;
    reg [DATA_WIDTH-1:0] internal_sar;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            internal_dis <= {DATA_WIDTH{1'b0}};
            internal_ges <= {DATA_WIDTH{1'b0}};
            internal_sar <= {DATA_WIDTH{1'b0}};
            dis_out      <= {DATA_WIDTH{1'b0}};
            ges_out      <= {DATA_WIDTH{1'b0}};
            sar_out      <= {DATA_WIDTH{1'b0}};
        end else begin
            reg [DATA_WIDTH-1:0] next_dis;
            reg [DATA_WIDTH-1:0] next_ges;
            reg [DATA_WIDTH-1:0] next_sar;

            // Stage 1: compute the raw sums
            next_dis = internal_dis + dis_in;
            next_ges = internal_ges + ges_in;
            next_sar = internal_sar + sar_in;

            // Stage 2: resolve carries from the computed sums
            if (next_dis >= 18'd60) begin
                next_dis = next_dis - 18'd60;
                next_ges = next_ges + 1'b1;
            end
            if (next_ges >= 18'd60) begin
                next_ges = next_ges - 18'd60;
                next_sar = next_sar + 1'b1;
            end

            // Stage 3: commit to the registers
            internal_dis <= next_dis;
            internal_ges <= next_ges;
            internal_sar <= next_sar;

            dis_out <= next_dis;
            ges_out <= next_ges;
            sar_out <= next_sar;
        end
    end
endmodule
