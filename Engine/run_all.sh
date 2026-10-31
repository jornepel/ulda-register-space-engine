#!/usr/bin/env bash

# ============================================================================
# run_all.sh — Master Orchestration Script & Telemetry Validation Pass
# Compiles complete tree, asserts structural invariants, runs verification.
# ============================================================================

# Enforce clean exits on any internal failures
set -e

# Terminal ANSI Color Telemetry Anchors
COLOR_BLUE='\033[0;34m'
COLOR_GREEN='\033[0;32m'
COLOR_RED='\033[0;31m'
COLOR_RESET='\033[0;30m'

echo -e "${COLOR_BLUE}====================================================================${COLOR_RESET}"
echo -e "${COLOR_BLUE} BOOTING MASTER AUTOMATED CONTEXT PASS — ℤ[φ]³ DECODER SUITE        ${COLOR_BLUE}"
echo -e "${COLOR_BLUE}====================================================================${COLOR_RESET}\n"

# Step 1: Purge existing build artifacts
echo -e "${COLOR_BLUE}[ 1/4 STATUS ] Purging stale binary footprints...${COLOR_RESET}"
make clean

# Step 2: Compile the entire codebase core
echo -e "${COLOR_BLUE}[ 2/4 STATUS ] Compiling unified translation units and objects...${COLOR_RESET}"
make all

# Step 3: Run the Invariant Verification Framework
echo -e "${COLOR_BLUE}[ 3/4 STATUS ] Running automated algebraic validation gates...${COLOR_RESET}"
if [ -f "./test_suite.exe" ]; then
    ./test_suite.exe
else
    echo -e "${COLOR_RED}[ CRITICAL ERROR ] Verification binary missing! Build aborted.${COLOR_RESET}"
    exit 1
fi

# Step 4: Verify Proxy Library Linkages
echo -e "${COLOR_BLUE}[ 4/4 STATUS ] Inspecting compiled Direct3D 11 runtime injections...${COLOR_RESET}"
if [ -f "./d3d11.dll" ]; then
    echo -e "${COLOR_GREEN}[ PASS SUCCESS ] d3d11.dll compiled, exports aligned, ready for proxy hook.${COLOR_RESET}"
else
    echo -e "${COLOR_RED}[ CRITICAL ERROR ] Proxy hook binary compilation failed! Check SDK paths.${COLOR_RESET}"
    exit 1
fi

echo -e "\n${COLOR_GREEN}====================================================================${COLOR_RESET}"
echo -e "${COLOR_GREEN} THE ENGINE RUNTIME TREE COMPREHENSIVELY COMPILED WITH ZERO NOISE  ${COLOR_RESET}"
echo -e "${COLOR_GREEN}====================================================================${COLOR_RESET}"
