`timescale 1ns / 1ps
// ============================================================================
// ULDA CPU CORE — THE LUM AS A HARDWIRED INSTRUCTION
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================
//
// This is the CPU core. It executes the LUM as a single instruction.
// No runtime. No interpreter. No operating system.
// The LUM is the instruction set.
//
// ============================================================================

module ulda_cpu_core #(
    parameter DATA_WIDTH = 32,
    parameter ADDR_WIDTH = 8
)(
    input  wire                     clk,
    input  wire                     rst_n,
    input  wire [7:0]               opcode,
    input  wire [DATA_WIDTH-1:0]    operand_a,
    input  wire [DATA_WIDTH-1:0]    operand_b,
    output reg  [DATA_WIDTH-1:0]    result,
    output reg                      flag_lock_72,
    output reg                      flag_breach
);

    // ────────────────────────────────────────────────────────────────
    // HARDWIRED CONSTANTS
    // ────────────────────────────────────────────────────────────────
    localparam RADIX        = 60;
    localparam INTERFACE_11 = 11;
    localparam OMITTED_6    = 6;
    localparam ROTATION_72  = 72;
    localparam SHIFT_8      = 8;
    localparam BOUNDARY_504 = 504;

    // ────────────────────────────────────────────────────────────────
    // OPCODES — THE LUM INSTRUCTION SET
    // ────────────────────────────────────────────────────────────────
    localparam OP_LUM_DROP   = 8'h01;  // Layer-drop via >> 8
    localparam OP_LUM_MOD    = 8'h02;  // Modulo 60 via subtraction
    localparam OP_LUM_LOCK   = 8'h03;  // 72° rotation lock
    localparam OP_LUM_INTERFACE = 8'h04;  // Interface 11 phase-lock
    localparam OP_LUM_BOUNDARY  = 8'h05;  // 504 boundary check

    // ────────────────────────────────────────────────────────────────
    // INTERNAL REGISTERS
    // ────────────────────────────────────────────────────────────────
    reg [DATA_WIDTH-1:0] tmp;
    reg [DATA_WIDTH-1:0] remainder;

    // ────────────────────────────────────────────────────────────────
    // THE LUM PIPELINE — SINGLE CYCLE EXECUTION
    // ────────────────────────────────────────────────────────────────
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            result        <= {DATA_WIDTH{1'b0}};
            flag_lock_72  <= 1'b0;
            flag_breach   <= 1'b0;
        end else begin
            // Default
            flag_lock_72 <= 1'b0;
            flag_breach  <= 1'b0;

            case (opcode)

                // ────────────────────────────────────────────────────
                // OP 01 — LAYER-DROP (>> 8)
                // ────────────────────────────────────────────────────
                OP_LUM_DROP: begin
                    result <= operand_a >> SHIFT_8;
                end

                // ────────────────────────────────────────────────────
                // OP 02 — MODULO 60 VIA SUBTRACTION (NO DIVISION)
                // ────────────────────────────────────────────────────
                OP_LUM_MOD: begin
                    tmp = operand_a;
                    // Subtraction loop for modulo 60
                    while (tmp >= RADIX) begin
                        tmp = tmp - RADIX;
                    end
                    result <= tmp;
                end

                // ────────────────────────────────────────────────────
                // OP 03 — 72° ROTATION LOCK
                // ────────────────────────────────────────────────────
                OP_LUM_LOCK: begin
                    tmp = operand_a;
                    // Subtraction loop for modulo 72
                    while (tmp >= ROTATION_72) begin
                        tmp = tmp - ROTATION_72;
                    end
                    if (tmp == 0) begin
                        result <= operand_a;
                        flag_lock_72 <= 1'b1;
                    end else begin
                        // Correction torque
                        result <= operand_a + (ROTATION_72 - tmp);
                        flag_lock_72 <= 1'b1;
                    end
                end

                // ────────────────────────────────────────────────────
                // OP 04 — INTERFACE 11 PHASE-LOCK
                // ────────────────────────────────────────────────────
                OP_LUM_INTERFACE: begin
                    tmp = operand_a;
                    // Subtraction loop for modulo 11
                    while (tmp >= INTERFACE_11) begin
                        tmp = tmp - INTERFACE_11;
                    end
                    result <= operand_a - tmp;
                end

                // ────────────────────────────────────────────────────
                // OP 05 — 504 BOUNDARY CHECK
                // ────────────────────────────────────────────────────
                OP_LUM_BOUNDARY: begin
                    if (operand_a > BOUNDARY_504) begin
                        flag_breach <= 1'b1;
                        result <= operand_a - BOUNDARY_504;
                    end else begin
                        result <= operand_a;
                    end
                end

                // ────────────────────────────────────────────────────
                // DEFAULT — NOP
                // ────────────────────────────────────────────────────
                default: result <= operand_a;

            endcase
        end
    end
endmodule
