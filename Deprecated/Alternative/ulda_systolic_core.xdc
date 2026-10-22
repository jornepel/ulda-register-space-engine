# Vivado Target Physical Design Constraints for ULDA Systolic Core
create_clock -period 1.000 -name core_clk [get_ports clk]

set_input_delay -clock core_clk -max 0.200 [get_ports {dis_in[*] ges_in[*] sar_in[*]}]
set_output_delay -clock core_clk -max 0.200 [get_ports {dis_out[*] ges_out[*] sar_out[*]}] 
