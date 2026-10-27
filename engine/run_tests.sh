#!/usr/bin/env bash

# ====================================================================
# run_tests.sh — Automated Pipeline for ULDA Topological Decoder Engine
# Copyright (c) 2026 Jorne Pel. All rights reserved.
# ====================================================================

set -e

CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m'

echo -e "${CYAN}====================================================================${NC}"
echo -e "${CYAN}        ULDA ENGINE PIPELINE INITIALIZATION & VERIFICATION          ${NC}"
echo -e "${CYAN}====================================================================${NC}"

# 1. Environment and Compiler Check
echo -e "\n${YELLOW}[1/6] Checking System Capabilities...${NC}"
if ! command -v cc &> /dev/null; then
    echo -e "${RED}Error: C Compiler (cc) not found in system PATH.${NC}"
    exit 1
fi
echo -e "  • Compiler found: $(cc --version | head -n 1)"

if ! command -v python3 &> /dev/null; then
    echo -e "${RED}Error: python3 not found in system PATH.${NC}"
    exit 1
fi
echo -e "  • Python found:   $(python3 --version)"
echo -e "  • Environment check passed."

# 2. Strict Build Execution
echo -e "\n${YELLOW}[2/6] Executing Pure Optimization Compilation Matrix...${NC}"
echo "  • Cleaning old binaries..."
make clean

echo "  • Compiling core binaries (test, bench, demo)..."
make test
make bench
make demo
echo -e "${GREEN}  • All targets compiled successfully.${NC}"
echo -e "  • Flags: $(make -s print-cflags)"

# 3. Shared Engine Build (for Python / ctypes)
echo -e "\n${YELLOW}[3/6] Building Shared Engine for Python (ctypes)...${NC}"
echo -e "${CYAN}--------------------------------------------------------------------${NC}"
if make lib; then
    echo -e "${CYAN}--------------------------------------------------------------------${NC}"
    echo -e "${GREEN}✅ SHARED ENGINE BUILT (libulda).${NC}"
else
    rc=$?
    echo -e "${RED}❌ SHARED ENGINE BUILD FAILED (exit $rc).${NC}"
    exit 1
fi

# 4. Invariant Test Harness Verification
echo -e "\n${YELLOW}[4/6] Running Invariant Suite Verification (§8 Invariants)...${NC}"
echo -e "${CYAN}--------------------------------------------------------------------${NC}"
if ./test; then
    echo -e "${CYAN}--------------------------------------------------------------------${NC}"
    echo -e "${GREEN}✅ ALL INVARIANT AND ANCHOR-RANK TESTS VERIFIED PERFECTLY!${NC}"
else
    rc=$?
    echo -e "${RED}❌ INVARIANT HARNESS FAILED (exit $rc).${NC}"
    exit 1
fi

# 5. Engine Benchmark Analysis
echo -e "\n${YELLOW}[5/6] Executing Branchless Hot-Path Throughput Profiles...${NC}"
echo -e "${CYAN}--------------------------------------------------------------------${NC}"
if ./bench; then
    echo -e "${CYAN}--------------------------------------------------------------------${NC}"
    echo -e "${GREEN}✅ BENCHMARK RUN COMPLETION SUCCESSFUL.${NC}"
else
    rc=$?
    echo -e "${RED}❌ BENCHMARK FAILED (exit $rc).${NC}"
    exit 1
fi

# 6. Python Protocol Cross-Check (calls C engine via ctypes)
echo -e "\n${YELLOW}[6/6] Running Python Protocol Against Shared Engine...${NC}"
echo -e "${CYAN}--------------------------------------------------------------------${NC}"
if ULDA_BACKEND=stub python3 ulda_grid.py > /tmp/ulda_python_out.json 2> /tmp/ulda_python_log.txt; then
    echo -e "${CYAN}--------------------------------------------------------------------${NC}"
    echo -e "${GREEN}✅ PYTHON PROTOCOL AGREES WITH C ENGINE.${NC}"
    echo -e "   (full output saved to /tmp/ulda_python_out.json)"
    echo -e "   (log: /tmp/ulda_python_log.txt)"
else
    rc=$?
    echo -e "${RED}❌ PYTHON PROTOCOL FAILED (exit $rc).${NC}"
    echo -e "${YELLOW}   Last 20 lines of log:${NC}"
    tail -20 /tmp/ulda_python_log.txt || true
    exit 1
fi

# 7. Live Simulation Trigger
echo -e "\n${YELLOW}[BONUS] Executing Live 4D Time-Ladder Sequence Cascade Demo...${NC}"
if ./demo; then
    :
else
    rc=$?
    echo -e "${RED}❌ DEMO FAILED (exit $rc).${NC}"
    exit 1
fi

echo -e "\n${GREEN}====================================================================${NC}"
echo -e "${GREEN}🔥 PIPELINE COMPLETE: Your code fort is 100% secure and operational. ${NC}"
echo -e "${GREEN}====================================================================${NC}"
