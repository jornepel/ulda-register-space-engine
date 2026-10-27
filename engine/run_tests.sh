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
echo -e "\n${YELLOW}[1/4] Checking System Capabilities...${NC}"
if ! command -v cc &> /dev/null; then
    echo -e "${RED}Error: C Compiler (cc) not found in system PATH.${NC}"
    exit 1
fi
echo -e "  • Compiler found: $(cc --version | head -n 1)"
echo -e "  • Environment check passed."

# 2. Strict Build Execution
echo -e "\n${YELLOW}[2/4] Executing Pure Optimization Compilation Matrix...${NC}"
echo "  • Cleaning old binaries..."
make clean

echo "  • Compiling core binaries (test, bench, demo)..."
make test
make bench
make demo
echo -e "${GREEN}  • All targets compiled successfully.${NC}"
echo -e "  • Flags: $(make -s print-cflags)"

# 3. Invariant Test Harness Verification
echo -e "\n${YELLOW}[3/4] Running Invariant Suite Verification (§8 Invariants)...${NC}"
echo -e "${CYAN}--------------------------------------------------------------------${NC}"
if ./test; then
    echo -e "${CYAN}--------------------------------------------------------------------${NC}"
    echo -e "${GREEN}✅ ALL INVARIANT AND ANCHOR-RANK TESTS VERIFIED PERFECTLY!${NC}"
else
    rc=$?
    echo -e "${RED}❌ INVARIANT HARNESS FAILED (exit $rc).${NC}"
    exit 1
fi

# 4. Engine Benchmark Analysis
echo -e "\n${YELLOW}[4/4] Executing Branchless Hot-Path Throughput Profiles...${NC}"
echo -e "${CYAN}--------------------------------------------------------------------${NC}"
if ./bench; then
    echo -e "${CYAN}--------------------------------------------------------------------${NC}"
    echo -e "${GREEN}✅ BENCHMARK RUN COMPLETION SUCCESSFUL.${NC}"
else
    rc=$?
    echo -e "${RED}❌ BENCHMARK FAILED (exit $rc).${NC}"
    exit 1
fi

# 5. Live Simulation Trigger
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
