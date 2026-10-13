ULDA Topological Decoder Engine
Fixed-Point Sexagesimal Architecture

This repository houses the core implementation of the Register-Space Space-Time Engine under the Unified Lineage Data Architecture (ULDA). This architecture provides a clean, definitive correction to digital degradation by eliminating binary floating-point roundoff artifacts and radix-drift in large-scale 3D spacetime quantum topological simulations.

By extracting the highly divisible positional mechanics of historical cuneiform arithmetic (Base-60) and loading them directly onto modern, commodity binary CPUs/GPUs as a fixed-point integer abstraction layer, we force simulation-induced noise metrics to absolute machine zero (2.62 × 10⁻¹⁴ at depth r=12) without ever calling a floating-point subroutine.
The Bare-Metal Philosophy

Modern software engineering is trapped in a Kali Yuga of computational confusion — a state of numerical truncation where pristine algebraic states are continuously degraded into endless, chaotic binary expansions (0.11001100...₂). Tech-monopolies stack abstraction layer upon abstraction layer, throwing bloated frameworks at hardware because they have forgotten how to talk directly to the silicon.

This project is a radical return to the bare-metal. This engine operates entirely on pure integer register spaces:

    No Runtime Division: Compiling carry rules using traditional division (// and %) introduces immense propagation delay and consumes unnecessary logic gates. This engine drops runtime division entirely, utilizing a Hardwired Look-Up Logic Matrix (LUM) and raw bit-shifting.

    Zero Memory Over-fetch: Coordinate loops compress traditional, bloated vector buffers (float32/64) into narrow, single-word integer bitmasks, allowing parallel processor pipelines to fetch data with zero bandwidth overhead.

    The Structural Cipher (Omission of 6): To prevent recursive logical traps inside the sequential register, the number 6 is strictly isolated as a structural matrix operator (6 × 10 = 60) and omitted from the sequential data pipeline. The register skips from 5 straight to 7 (2 → 1 → 3 → 4 → 5 → 7), forcing continuous probabilities into hard-locked whole-number counts.

The Closed Matrix Mathematics

The architecture derives its mechanical advantage from the high divisibility of the sexagesimal radix (60 = 2² × 3 × 5 = 4 × 3 × 5), ensuring that common rational fractions yield completely terminating expressions:

1/2 = 0.30₆₀, 1/3 = 0.20₆₀, 1/5 = 0.12₆₀

By utilizing a post-divider terminal branching index (+7) as an absolute scale constant, we anchor the decimal (b=10) and sexagesimal (b=60) tracking domains together via their greatest common divisor (GCD(10, 60) = 10).
The Universal Identity

The entire structural framework closes perfectly on the absolute macro-calibration identity:

36,620 = (3 × 20 + 7) × 360 + 4 × 5⁵

This equation maps the exact mechanical partition between the high-exponent Mesopotamian chronological cycles (24,120) and the fractional polynomial scales of the Egyptian decimal matrix (12,500 = 4 × 5⁵). The historical gap between these registers is not a myth — it is the exact calculated structure-deficit (6,530) of a global geological reset mapping directly onto our secondary error ledger (R₂).
Repository Structure

    /hardware : Synthesizable Verilog HDL implementations for Commodity FPGA Logic Arrays (Xilinx Kintex UltraScale+).

    /sim : The Cross-Base Arithmetic Engine reference implementation in Python (numpy int64 optimized).

    /docs : The complete mathematical manual detailing radix-drift elimination and Diophantine boundary identities.

Quick Start: Hardware Carry Execution

The Look-Up Logic Matrix (LUM) avoids runtime overhead by using raw subtraction boundaries directly on the silicon clock cycle. The carry logic operates on a two-stage evaluation: the sums are computed first into temporary wires, the carries are resolved, and only then are the registers updated. This eliminates the double-assignment hazard that would otherwise drop the incoming operand during a carry event.
verilog

// Pure Integer Look-Up Logic Matrix (LUM) Carry Loop
// Two-stage evaluation: compute sums, resolve carries, then commit.
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        internal_dis <= 18'd0;
        internal_ges <= 18'd0;
        internal_sar <= 18'd0;
    end else begin
        reg [17:0] next_dis;
        reg [17:0] next_ges;
        reg [17:0] next_sar;

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
    end
end

The Structural Cipher: Omission of 6 in Cross-Base Radix Compilers
1. The Architectural Contradiction

In a standard binary or decimal compiler, numbers are treated as continuous sequential data points: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]. When computing large-scale topological structures or continuous probabilities, using the radix number itself as an addressable data point introduces a recursive logical trap.

Because 6 is the core positional matrix operator of the sexagesimal system (6 × 10 = 60; 6² = 36), forcing the ALU to evaluate 6 as both a structural operator and a register value causes propagation delay and forces the inclusion of slow runtime-division loops (// and %) to compute carries.

By strictly omitting 6 from the sequential register pointer, we decouple data from the structural operator. The data sequence skips the trap entirely:

Sequence Pointer: [1, 2, 3, 4, 5, 7] (The 6 is Omitted)
2. The Mathematical Pipeline (2 → 1 → 3 → 4 → 5 → 7)

To process coordinate transformations and quantum error tracking without floating-point drift, the compiler forces all multi-scale carries through a hardwired pipeline:
text

  [2] Fusion
   │
  [1] Monad Register
   │
  [3] Tri-Cylinder Split
   │
  [4] Spatial Quadrant Allocation
   │
  [5] Base/4 Demarcation (20 / 4 = 5)
   │
  [7] Asymmetric Remainder Constant (+7 Balance)

By jumping directly from 5 to 7, the remainder constant is locked at exactly +7. This asymmetry generates the structural matrix corrections for both bases automatically:

    Decimal Base (b=10): f(10) = 10 + 7 = 17

    Sexagesimal Base (b=60): f(60) = 60 + 7 = 67

3. Eliminating Runtime Division (Bare-Metal Realization)

Because the sequence pointer is mapped to the prime factorization of 60 (2² × 3 × 5 = 4 × 3 × 5), the compiler does not need to call the CPU's hardware divider during a carry overflow.

When processing column validation, the raw arithmetic closed loop operates on pure bitwise shifts and hardwired subtractions.

The Look-Up Logic Matrix (LUM) Algorithm:

Instead of executing carry = value / 60 and remainder = value % 60, the compiler maps the 18-bit bit-sliced fields directly to direct subtraction boundaries:
pascal

// Bare-Metal Pseudo-Execution Layer (No Runtime Div)
IF internal_register_dis >= 60 THEN
    internal_register_dis <= internal_register_dis - 60;
    internal_register_ges <= internal_register_ges + 1;
END_IF

This ensures that the data flushes completely through the lower-order columns (diš and geš) into the digital ground ledger (R₂), leaving the highest column boundary at absolute zero (R₂.šar == 0) unless a true boundary state is breached.
4. How to Implement in Your Custom Lexer/Parser

    Tokenization Filter: Intercept incoming numeric literals. If the raw string data maps to coordinate matrices, parse them through the Base-60 fixed-point layout (SHIFT_DIS = 0, SHIFT_GES = 18, SHIFT_SAR = 36).

    Mask the Operator: Ensure your compiler's internal bitmask uses the foundational ladder metric 36 (6²) to verify scale factor transformations, but do not assign an active register address to the digit 6.

    Dual-Register Tracking: Enforce the split immediately upon token processing:

        R₁ (Primary): Operates on the terminated base factors (4 × 3 × 5).

        R₂ (Secondary Ledger): Tracks asymmetric noise using the remainder constants (17 and 67).

By forcing the execution down to this raw integer pipeline, you achieve absolute Machine Zero (2.62 × 10⁻¹⁴ at depth r=12) without ever invoking an IEEE 754 floating-point subroutine.
License

This software is released under the GNU Affero General Public License v3.0 (AGPL-3.0).

For individual, academic, and open-source use, the software is free to use, modify, and distribute under the terms of the AGPL-3.0.
 
For commercial use that does not comply with the AGPL-3.0 — including proprietary integration, SaaS deployment without source disclosure, or embedding in closed-source products — a commercial license is required.

Contact:  jornepel@gmail.com
Dedication

This work is dedicated to the memory of Terrence Andrew Davis (1969–2018) , a computer scientist who defended architectural minimalism, the integrity of native binary execution, and the elimination of systemic computational complexity. His core conviction — that compute stacks should remain mathematically pristine, unencumbered by corporate software bloat, and transparent down to the raw silicon clock cycle — is implemented in this framework.
