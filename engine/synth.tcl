# ============================================================================
# ULDA Systolic Core — Vivado Synthesis Script
# Target: Xilinx Kintex UltraScale+ (or adjust to your FPGA)
# License: AGPL-3.0
# Contact: JornePel@gmail.com
# Dedicated to Terrence Andrew Davis (1969-2018).
# ============================================================================

# 1. Create a new project
create_project ulda_systolic ./build -part xcku040-ffva1156-2-e -force

# 2. Add the Verilog source
add_files -norecurse ./ulda_systolic_core.v

# 3. Set the top module
set_property top ulda_systolic_core [current_fileset]

# 4. Launch synthesis
launch_runs synth_1 -jobs 8
wait_on_run synth_1

# 5. Implementation
launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1

# 6. Report
open_run impl_1
report_utilization -file ./build/utilization.rpt
report_timing_summary -file ./build/timing.rpt

puts "ULDA Systolic Core — Synthesis complete."
puts "Bitstream: ./build/ulda_systolic.runs/impl_1/ulda_systolic_core.bit"
