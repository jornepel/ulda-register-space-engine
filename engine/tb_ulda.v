`timescale 1ns / 1ps
// ============================================================================
// ULDA Systolic Core — Testbench
// Verifies the two-stage carry logic: 60 × dis_in should produce
// one carry into ges, leaving dis = 0, ges = 1, sar = 0.
//
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================

module tb_ulda;

    reg         clk   = 0;
    reg         rst_n = 0;
    reg  [17:0] dis_in = 0;
    reg  [17:0] ges_in = 0;
    reg  [17:0] sar_in = 0;
    wire [17:0] dis_out;
    wire [17:0] ges_out;
    wire [17:0] sar_out;

    // Device under test
    ulda_systolic_core dut (
        .clk     (clk),
        .rst_n   (rst_n),
        .dis_in  (dis_in),
        .ges_in  (ges_in),
        .sar_in  (sar_in),
        .dis_out (dis_out),
        .ges_out (ges_out),
        .sar_out (sar_out)
    );

    // 100 MHz clock
    always #5 clk = ~clk;

    initial begin
        // Waveform dump
        $dumpfile("ulda.vcd");
        $dumpvars(0, tb_ulda);

        // Release reset
        #10 rst_n = 1;

        // --------------------------------------------------------------
        // Test 1: 60 × dis_in = 1 → should carry into ges
        // --------------------------------------------------------------
        repeat (60) begin
            dis_in = 1;
            #10;
        end
        dis_in = 0;
        #20;

        $display("Test 1 — 60 × dis_in = 1");
        $display("  dis = %0d, ges = %0d, sar = %0d", dis_out, ges_out, sar_out);
        $display("  Expected: dis = 0, ges = 1, sar = 0");

        if (dis_out == 0 && ges_out == 1 && sar_out == 0)
            $display("  PASS");
        else
            $display("  FAIL");

        // --------------------------------------------------------------
        // Test 2: 60 × ges_in = 1 → should carry into sar
        // --------------------------------------------------------------
        // (carry reset via rst_n to isolate the test)
        rst_n = 0;
        #10 rst_n = 1;

        repeat (60) begin
            ges_in = 1;
            #10;
        end
        ges_in = 0;
        #20;

        $display("Test 2 — 60 × ges_in = 1");
        $display("  dis = %0d, ges = %0d, sar = %0d", dis_out, ges_out, sar_out);
        $display("  Expected: dis = 0, ges = 0, sar = 1");

        if (dis_out == 0 && ges_out == 0 && sar_out == 1)
            $display("  PASS");
        else
            $display("  FAIL");

        // --------------------------------------------------------------
        // Test 3: one carry from dis AND one from ges
        // --------------------------------------------------------------
        rst_n = 0;
        #10 rst_n = 1;

        // 60 in dis → carry to ges
        repeat (60) begin
            dis_in = 1;
            #10;
        end
        dis_in = 0;

        // 60 in ges → carry to sar
        repeat (60) begin
            ges_in = 1;
            #10;
        end
        ges_in = 0;
        #20;

        $display("Test 3 — carry chain dis → ges → sar");
        $display("  dis = %0d, ges = %0d, sar = %0d", dis_out, ges_out, sar_out);
        $display("  Expected: dis = 0, ges = 0, sar = 1");

        if (dis_out == 0 && ges_out == 0 && sar_out == 1)
            $display("  PASS");
        else
            $display("  FAIL");

        $finish;
    end

endmodule
