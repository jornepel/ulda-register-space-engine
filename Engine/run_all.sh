#!/usr/bin/env bash
# ========================================================================
# run_all.sh — Complete Orchestration & Telemetry Runner for the ULDA Engine
# ========================================================================
set -e # Terminate script immediately if any compilation stage fails

# Color output codes for terminal logging
GREEN='\033[1;32m'
CYAN='\033[1;36m'
YELLOW='\033[1;33m'
RESET='\033[0m'

echo -e "${CYAN}====================================================================${RESET}"
echo -e "${CYAN}      LAUNCHING INTEGRATED ULDA TOPOLOGICAL DECODER SUITE           ${RESET}"
echo -e "${CYAN}====================================================================${RESET}"

# Step 1: Wipe stale binaries and trigger a clean project build
echo -e "\n${YELLOW}[Stage 1/6] Cleaning and Building Silicon Binaries via Makefile...${RESET}"
make clean
make all
make lib

# Step 2: Run the exact mathematical invariant unit checks
echo -e "\n${YELLOW}[Stage 2/6] Verifying Exact Metric and Structural Invariants...${RESET}"
echo "--------------------------------------------------------------------"
./test
echo "--------------------------------------------------------------------"

# Step 3: Run the 240 distinct chord projections
echo -e "\n${YELLOW}[Stage 3/6] Mapping 240 Observers-to-Vertices Dodecahedral Chords...${RESET}"
echo "--------------------------------------------------------------------"
./demo
echo "--------------------------------------------------------------------"

# Step 4: Run the raw processing throughput velocity benchmarks
echo -e "\n${YELLOW}[Stage 4/6] Measuring Hot-Path Core Primitive Instruction Speed...${RESET}"
echo "--------------------------------------------------------------------"
./bench
echo "--------------------------------------------------------------------"

# Step 5: Execute the multi-scale cosmic horizon simulation suites
echo -e "\n${YELLOW}[Stage 5/6] Simulating Multi-Scale Cosmic Horizon Profiles...${RESET}"
echo "--------------------------------------------------------------------"
./cosmos
echo "--------------------------------------------------------------------"

# Step 6: Trigger the twin Python visual graph profilers
echo -e "\n${YELLOW}[Stage 6/6] Launching Dashboard Graphs (A Major Gear Shifts)...${RESET}"
read -p "Press [Enter] to display the Counter-Rotational Gearing Map..."
python3 ulda_graph.py

echo -e "\n${YELLOW}Launching Dashboard Graphs (Live X Tensor Cross-Talk Lines)...${RESET}"
read -p "Press [Enter] to display the Inter-Quadrant Non-Local Transfer Profile..."
python3 ulda_graph.py tensor

echo -e "\n${YELLOW}[Stage 7/7] Executing Persistent Data Recorder and Stream Log...${RESET}"
python3 ulda_logger.py

echo -e "\n${GREEN}====================================================================${RESET}"
echo -e "${GREEN}[✓] ALL PIPELINES REFRESHED: Mathematical Invariants Secure.         ${RESET}"
echo -e "${GREEN}    Scale is an illusion. The Song is operating cleanly.           ${RESET}"
echo -e "${GREEN}====================================================================${RESET}"
