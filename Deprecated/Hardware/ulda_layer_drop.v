`timescale 1ns / 1ps
// ============================================================================
// ULDA LAYER-DROP ENGINE — BARE-METAL >> 8 WITHOUT LINEAR ZERO (OPTIMIZED)
// Target: Xilinx Kintex UltraScale+ / Commodity FPGA Logic Arrays
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
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
    // COMBINATORIAL PIPELINE REGISTERS
    // ────────────────────────────────────────────────────────────────
    reg [DATA_WIDTH-1:0] w_60_3;
    reg [DATA_WIDTH-1:0] w_60_2;
    reg [DATA_WIDTH-1:0] w_60_1;
    reg [DATA_WIDTH-1:0] w_60_0;
    reg [DATA_WIDTH-1:0] w_feedback_raw;
    reg [DATA_WIDTH-1:0] w_feedback_final;
    reg [DATA_WIDTH-1:0] w_mod72;

    // ────────────────────────────────────────────────────────────────
    // PARALLEL HARDWIRED MECHANICS (ASYNCHRONOUS LOGIC)
    // ────────────────────────────────────────────────────────────────
    always @(*) begin
        // Stage 1 & 2 — Interface 11 phase-lock (veilig aftrekken)
        if (vec_in >= INTERFACE_11)
            w_60_3 = vec_in - INTERFACE_11;
        else
            w_60_3 = vec_in;

        // Stage 3 — Layer-Drop via hardware routing (>> 8)
        w_60_2 = w_60_3 >> SHIFT_8;
        w_60_1 = w_60_2 >> SHIFT_8;
        w_60_0 = w_60_1 >> SHIFT_8;

        // Stage 4 — Residual bitmask absorption
        w_feedback_raw = (w_60_3 & 32'hFF)
                       + (w_60_2 & 32'hFF)
                       + (w_60_1 & 32'hFF)
                       + (w_60_0 & 32'hFF);

        if (w_feedback_raw >= OMITTED_6)
            w_feedback_final = w_feedback_raw - OMITTED_6;
        else
            w_feedback_final = w_feedback_raw;

        // Stage 6 — Synthesizable Hardware Modulo 72 (Bitshift Ladder)
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
            layer_60_3  <= {DATA_WIDTH{1'b0}};
            layer_60_2  <= {DATA_WIDTH{1'b0}};
            layer_60_1  <= {DATA_WIDTH{1'b0}};
            layer_60_0  <= {DATA_WIDTH{1'b0}};
            feedback_6  <= {DATA_WIDTH{1'b0}};
            lock_72     <= 1'b0;
        end else if (step_en) begin
            // Foutloze niet-blokkerende hardware commit
            layer_60_3  <= w_60_3;
            layer_60_2  <= w_60_2;
            layer_60_1  <= w_60_1;
            layer_60_0  <= w_60_0;
            feedback_6  <= w_feedback_final;
            
            // 72° rotation lock check op basis van de hardwired modulo
            if (w_mod72 == 0)
                lock_72 <= 1'b1;
            else
                lock_72 <= 1'b0;
        end
    end
endmodule
