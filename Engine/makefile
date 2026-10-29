CC      ?= cc
CFLAGS  ?= -O3 -march=native -flto -fomit-frame-pointer -Wall -Wextra -std=c11 -DBUILDING_ULDA_DLL
LDFLAGS ?= -flto
LDLIBS  ?=

.PHONY: all clean lib print-asm visual

# Isolated independent binary streams
all: test bench demo cosmos tensor emu mutant-bench d3d11.dll main visual

.DELETE_ON_ERROR:

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
cosmos: cosmos.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

tensor: tensor.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

emu: emu.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

main: main.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
mutant-bench: ulda_mutated_bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

audio: ulda_audio.o ulda.o puzzles.o ulda_shim.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
visual: ulda_visual.o ulda.o puzzles.o ulda_shim.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lgdi32 -lwinmm -mwindows
	
# ---- Shared library rules for cross-platform linking ----
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    SHARED_EXT   = dylib
    SHARED_FLAGS = -dynamiclib
else ifeq ($(OS),Windows_NT)
    SHARED_EXT   = dll
    SHARED_FLAGS = -shared
else
    SHARED_EXT   = so
    SHARED_FLAGS = -shared
endif
	
d3d11.dll: ulda_d3d.o ulda.o puzzles.o ulda_shim.o
	$(CC) $(SHARED_FLAGS) -o $@ $^ $(LDLIBS)

# Explicit position-independent code separation rules
cosmos.o: ulda_cosmos.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ ulda_cosmos.c

tensor.o: ulda_tensor.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

emu.o: ulda_emu.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -UBUILDING_ULDA_DLL -fPIC -c -o $@ $<

main.o: main.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

ulda_d3d.o: ulda_d3d.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

libulda.$(SHARED_EXT): ulda_shim.o ulda.o
	$(CC) $(SHARED_FLAGS) -o $@ $^

ulda_shim.o: ulda_shim.c ulda.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

ulda.o: ulda.c ulda.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

ulda_mutated_bench.o: ulda_mutated_bench.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

print-asm: bench.c ulda.c ulda.h
	$(CC) $(CFLAGS) -S -fverbose-asm -o bench.s bench.c

lib: libulda.$(SHARED_EXT)

test.o:    test.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ $<

bench.o:   bench.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

puzzles.o: puzzles.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ $<

demo.o:    demo.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ $<

ulda_audio.o: ulda_audio.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -UBUILDING_ULDA_DLL -fPIC -c -o $@ $<

ulda_visual.o: ulda_visual.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -UBUILDING_ULDA_DLL -fPIC -c -o $@ $<

clean:
	rm -f *.o test test.exe bench bench.exe demo demo.exe cosmos cosmos.exe tensor tensor.exe emu emu.exe main main.exe mutant-bench mutant-bench.exe d3d11.dll libulda.so libulda.dylib libulda.dll ulda_telemetry_stream.json visual visual.exe
