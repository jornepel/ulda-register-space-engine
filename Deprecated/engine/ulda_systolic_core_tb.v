`timescale 1ns / 1ps
// ============================================================================
// ULDA SYSTOLIC CORE — PORT-11 INTERFACE TESTBENCH
// Target: Vivado Behavioral Simulator / Native Logic Validation
// License: AGPL-3.0
// Dedication: Terrence Andrew Davis (1969-2018).
// ============================================================================

module ulda_systolic_core_tb;

    parameter DATA_WIDTH = 18;

    // Inputs naar de core
    reg                    clk;
    reg                    rst_n;
    reg  [DATA_WIDTH-1:0]  dis_in;
    reg  [DATA_WIDTH-1:0]  ges_in;
    reg  [DATA_WIDTH-1:0]  sar_in;

    // Outputs vanuit de core
    wire [DATA_WIDTH-1:0]  dis_out;
    wire [DATA_WIDTH-1:0]  ges_out;
    wire [DATA_WIDTH-1:0]  sar_out;

    // Instantiatie van de gereinigde silicium core
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

    // Genereer de basistact (Klokpuls van het metaal)
    always #5 clk = ~clk;

    initial begin
        // Initialiseer het register op absolute aanwezigheid (geen nul)
        clk = 0;
        rst_n = 0;
        dis_in = 0;
        ges_in = 0;
        sar_in = 0;

        #10;
        rst_n = 1; // Vrijgeven van het silicium
        #10;

        $display("=========================================================");
        $display("START ULDA TOPOLOGICAL CLOCK-VECTOR VERIFICATION");
        $display("=========================================================");

        // Stap 1: Injecteer de poort-11 interface factor (Eerste puls)
        $display("[Tijd: %0t] Injecteer Poort-11 Interface Correctie...", $time);
        dis_in = 18'd11; 
        #10;
        dis_in = 18'd0; // Reset input, laat de systolic array propageren
        #20;
        $display("Status na Poort-11: DIS=%0d, GES=%0d, SAR=%0d", dis_out, ges_out, sar_out);

        // Stap 2: Activeer de volledige cyclus-som (22 = 2 x 11)
        // Dit activeert de carry-logic over de 6-grens van het register
        $display("[Tijd: %0t] Voltooi de 22 Sequence Correctie (1+2+3+4+5+7)...", $time);
        dis_in = 18'd49; // 11 + 49 = 60 (Modulo-6 register inklapgrens)
        #10;
        dis_in = 18'd0;
        #20;

        // Het register moet nu de 60 (6) geraakt hebben en doorsijpelen naar GES
        $display("Status na Sequence Sluiting: DIS=%0d, GES=%0d, SAR=%0d", dis_out, ges_out, sar_out);

        // Stap 3: Controleren van de Nulsom-convergentie
        if (ges_out == 18'b1 && dis_out == 18'b0) begin
            $display("=========================================================");
            $display("SUCCESS: Het register ademt. De 6-grens heeft gewerkt.");
            $display("De vector is gecorrigeerd via de interface.");
            $display("=========================================================");
        end else begin
            $display("ERROR: Systeembreuk gedetecteerd in de matrix.");
        end

        $finish;
    end

endmodule
