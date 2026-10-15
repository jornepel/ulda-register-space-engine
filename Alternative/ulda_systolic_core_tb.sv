`timescale 1ns / 1ps
// ============================================================================
// ULDA SYSTOLIC CORE — HARDWARE TESTBENCH (TIMING CORRECTED)
// AUTOMATED VERIFICATION OF THE SEXAGESIMAL REGISTER INTERFACE
// License: AGPL-3.0
// Contact: JornePel@gmail.com
// Dedicated to Terrence Andrew Davis (1969-2018).
// ============================================================================

module ulda_systolic_core_tb;

    parameter DATA_WIDTH = 18;
    
    // Systeemsignalen
    reg                    clk;
    reg                    rst_n;
    reg  [DATA_WIDTH-1:0]  dis_in;
    reg  [DATA_WIDTH-1:0]  ges_in;
    reg  [DATA_WIDTH-1:0]  sar_in;
    
    wire [DATA_WIDTH-1:0]  dis_out;
    wire [DATA_WIDTH-1:0]  ges_out;
    wire [DATA_WIDTH-1:0]  sar_out;

    // Unit Under Test (UUT)
    ulda_systolic_core #(
        .DATA_WIDTH(DATA_WIDTH)
    ) uut (
        .clk(clk),
        .rst_n(rst_n),
        .dis_in(dis_in),
        .ges_in(ges_in),
        .sar_in(sar_in),
        .dis_out(dis_out),
        .ges_out(ges_out),
        .sar_out(sar_out)
    );

    // Klokgenerator: Exact 1ns periode (1 GHz core frequency)
    always #0.5 clk = ~clk;

    // Helper task om data veilig op de vallende flank (negedge) te injecteren.
    // Dit voorkomt Setup/Hold timing violations op de 1 GHz stijgende flank!
    task inject_dis(input [DATA_WIDTH-1:0] value);
        begin
            @(negedge clk);
            dis_in = value;
            @(negedge clk);
            dis_in = 18'd0;
        end
    endtask

    initial begin
        // Initials
        clk    = 1'b0;
        rst_n  = 1'b0;
        dis_in = {DATA_WIDTH{1'b0}};
        ges_in = {DATA_WIDTH{1'b0}};
        sar_in = {DATA_WIDTH{1'b0}};

        // Resetfase
        #2;
        @(negedge clk);
        rst_n = 1'b1;
        #1;

        // TEST 1: De basis-puls (1 eenheid in de DIS-matrix)
        $display("[START] Injectie van basis-pulsen...");
        inject_dis(18'd1);
        repeat(5) @(posedge clk); // Wacht 5 klokcycli op propagatie

        // TEST 2: De Poort 11 en Sequentie-som (22)
        $display("[STAP] Schone invoer van Sequentie-som (22 = 2 x 11)...");
        inject_dis(18'd22);
        repeat(5) @(posedge clk);

        // TEST 3: De Hardware Rollover Matrix (Geforceerde oversturing naar GES)
        $display("[STAP] Testen van de harde Base-60 omslaggrens...");
        inject_dis(18'd45); // 45 + bestaande waarden triggert rollover (> 60)
        repeat(5) @(posedge clk);

        // Controleer of de output schoon is geland
        $display("==================================================");
        $display("HARDWARE REGISTER STATUS OUTPUT:");
        $display("DIS (0.01_60) : %d", dis_out);
        $display("GES (0.10_60) : %d", ges_out);
        $display("SAR (1.00_60) : %d", sar_out);
        $display("==================================================");
        
        if (ges_out > 0) begin
            $display("[SUCCES] Carry-logic functioneert zonder floating-points.");
        end else begin
            $display("[FOUT] Systeemstoring in de registerketen.");
        end

        $finish;
    end

endmodule
