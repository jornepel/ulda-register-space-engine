# ============================================================================
# Makefile — High-Performance MSYS2/MinGW64 Build Configuration System
# Targets: Windows x86_64, Optimized for hardware acceleration.
# ============================================================================

# Toolchain Definitions
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O3 -msse4.2 -mpclmul -march=native -funroll-loops
LDFLAGS = -shared
LIBS    = -luser32 -lgdi32 -ld3d11 -ldxgi -lws2_32 -lwinmm

# Target Deliverables
UNIFIED_SRC = ulda_unified.c
UNIFIED_OBJ = ulda_unified.o
STATIC_LIB  = libulda.a
PROXY_DLL   = d3d11.dll

# Test & Executable Binaries
TEST_BIN    = test_suite.exe
BENCH_BIN   = bench.exe
EMU_SRC     = ulda_emu.c
AUDIO_SRC   = ulda_audio.c
VISUAL_SRC  = ulda_visual.c
D3D_SRC     = ulda_d3d.c

.PHONY: all clean test library proxy visual bench

# 1. Master Command Sequence
all: library test proxy bench

# 2. Compile Core Unified Translation Unit & Static Archive
library:
	$(CC) $(CFLAGS) -c $(UNIFIED_SRC) -o $(UNIFIED_OBJ)
	ar rcs $(STATIC_LIB) $(UNIFIED_OBJ)

# 3. Build Automated Invariant Verification Test Suite
test: library
	$(CC) $(CFLAGS) test_unified.c $(UNIFIED_OBJ) -o $(TEST_BIN) $(LIBS)

# 4. Build High-Performance Nano-Benchmark
bench: library
	$(CC) $(CFLAGS) bench.c $(UNIFIED_OBJ) -o $(BENCH_BIN) $(LIBS)

# 5. Compile the Active Direct3D 11 Proxy Interception DLL
proxy: library
	$(CC) $(CFLAGS) $(LDFLAGS) $(D3D_SRC) $(EMU_SRC) $(UNIFIED_OBJ) $(LIBS) -o $(PROXY_DLL)

# 6. Build Standalone Desktop Visual Projector Target
visual: library
	$(CC) $(CFLAGS) main_visual_stub.c $(VISUAL_SRC) $(AUDIO_SRC) $(UNIFIED_OBJ) $(LIBS) -o visual_projector.exe

# 7. Purge Intermediate Objects & Binary Artifacts
clean:
	rm -f *.o *.a *.exe *.dll *.log
