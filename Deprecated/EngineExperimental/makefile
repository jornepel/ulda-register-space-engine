CC      ?= cc
CFLAGS  ?= -O3 -march=native -flto -fomit-frame-pointer -Wall -Wextra -std=c11
LDFLAGS ?= -flto
LDLIBS  ?=

.PHONY: all run run-bench run-demo run-cosmos run-tensor run-emu run-mutant-bench clean lib print-cflags print-asm

# 1. Added mutant-bench to the master compilation block
all: test bench demo cosmos tensor emu mutant-bench d3d11.dll

.DELETE_ON_ERROR:

# Standard compiled objects ONLY (No custom implementations here)
OBJS = test.o bench.o puzzles.o demo.o

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
cosmos: cosmos.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

tensor: tensor.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

emu: emu.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
mutant-bench: ulda_mutated_bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# ---- Shared library rules for cross-platform linking ----
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    SHARED_EXT   = dylib
    SHARED_FLAGS = -dynamiclib
else
    SHARED_EXT   = so
    SHARED_FLAGS = -shared
endif

d3d11.dll: ulda_d3d.o ulda.o puzzles.o
	$(CC) $(SHARED_FLAGS) -o $@ $^ $(LDLIBS)

# Explicit rules matching exact filenames with position-independent compliance
cosmos.o: ulda_cosmos.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ ulda_cosmos.c

tensor.o: ulda_tensor.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

emu.o: ulda_emu.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

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
	@echo "--------------------------------------------------------------------"
	@echo "[✓] Assembly successfully extracted to workspace file: bench.s"
	@echo "    Open bench.s to view the pre-calculated hardware register folds."
	@echo "--------------------------------------------------------------------"

lib: libulda.$(SHARED_EXT)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test.o:    ulda.h puzzles.h
bench.o:   ulda.h
puzzles.o: ulda.h puzzles.h
demo.o:    ulda.h puzzles.h

run: test
	./test

run-bench: bench
	./bench

run-demo: demo
	./demo

run-cosmos: cosmos
	./cosmos

run-tensor: tensor
	./tensor

run-emu: emu
	./emu

run-mutant-bench: mutant-bench
	./mutant-bench

.PHONY: print-cflags
print-cflags:
	@echo '$(CFLAGS)'

# 2. Hardened cleanup array explicitly including the mutant targets
clean:
	rm -f *.o test test.exe bench bench.exe demo demo.exe cosmos cosmos.exe tensor tensor.exe emu emu.exe mutant-bench mutant-bench.exe d3d11.dll libulda.so libulda.dylib
