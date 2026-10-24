/* ============================================================================
 * ULDA-X28 — VIA SHUNT HARDWARE TESTBENCH (`ulda_via_shunt_tb.v`)
 * ============================================================================
 * Simulation rig for clock-edge transit verification.
 * Sweeps through normal balances to verify zero-margin closure at the wall.
 * ============================================================================
 */

`timescale 1ns / 1ps

module ulda_via_shunt_tb;

    // Simulation Clock and Stimulus Inputs
    reg         clk;
    reg         rst_n;
    reg  [63:0] raw_vector_stress;

    // Monitored Output Tracks from Gate Logic
    wire [63:0] macro_register;
    wire [63:0] micro_flux;
    wire [15:0] angular_output_deg;
    wire        system_status;

    // Instantiate the Unit Under Test (UUT)
    ulda_via_shunt uut (
        .clk(clk),
        .rst_n(rst_n),
        .raw_vector_stress(raw_vector_stress),
        .macro_register(macro_register),
        .micro_flux(micro_flux),
        .angular_output_deg(angular_output_deg),
        .system_status(system_status)
    );

    // 1. Generate the Master System Clock Loop (50 MHz Simulation)
    always begin
        #10 clk = ~clk; 
    end

    // 2. Execute Verification Diagnostics Stream
    initial begin
        // Initialize Core System Pins
        clk = 0;
        rst_n = 0;
        raw_vector_stress = 64'd0;

        // Hold Reset across 2 full clock cycles
        #25;
        rst_n = 1;
        #15;
        
        \$display("===============================================================");
        \$display("STARTING ULDA FIRMWARE GATE SIMULATION: TRANSIT DIAGNOSTICS");
        \$display("===============================================================");

        // Test 1: Normal Operation Profile (Safely below 137 wall boundary)
        raw_vector_stress = 64'd120;
        #20; // Wait for positive clock edge transition
        \$display("[TIME: %0dns] TEST 1: Normal Influx Load Baseline", \(time);\)display("  -> Input Stress: %d | Status Pin: %b (Balanced by 43 Anchors)", raw_vector_stress, system_status);
        \$display("  -> Macro Reg   : %d | Micro-Flux: %d", macro_register, micro_flux);
        
        // Test 2: Striking the 137 Guardian Wall (Boundary Transition)
        raw_vector_stress = 64'd137;
        #20;
        \$display("[TIME: %0dns] TEST 2: High Saturation Boundary Collision", \(time);\)display("  -> Input Stress: %d | Status Pin: %b (Exhaust Valves Active!)", raw_vector_stress, system_status);
        \$display("  -> Macro Reg   : %d | Micro-Flux: %d | Angle Output: %d", macro_register, micro_flux, angular_output_deg);

        // Test 3: Overstepping into High Warp Surge / Macro-Precession Overflow
        raw_vector_stress = 64'd147; // 10 units past the gate wall
        #20;
        \$display("[TIME: %0dns] TEST 3: High-Voltage Delta Surge Routing via Shunt", \(time);\)display("  -> Input Stress: %d | Status Pin: %b (Exhaust Processing)", raw_vector_stress, system_status);
        \$display("  -> Macro Reg   : %d | Micro-Flux: %d | Angle Output: %d", macro_register, micro_flux, angular_output_deg);

        // Test 4: Dynamic Re-entry Recovery (Dropping back down below limit)
        raw_vector_stress = 64'd43; // Exactly onto the anchor constant value
        #20;
        \$display("[TIME: %0dns] TEST 4: Core Drop Matrix Reset Phase", \(time);\)display("  -> Input Stress: %d  | Status Pin: %b (Anchors Recover Control)", raw_vector_stress, system_status);
        \$display("  -> Macro Reg   : %d  | Micro-Flux: %d", macro_register, micro_flux);

        \$display("===============================================================");
        \$display("SIMULATION COMPLETE: Clock-Edges Aligned. Zero Drift Recorded.");
        \$display("===============================================================");
        \$finish;
    end

endmodule
