# Makefile — ULDA Compass Engine
# -----------------------------------------------------------------------------
# Builds the engine (ulda), the puzzles, the test, the benchmark, and the demo.
#
# Targets:
#   make all        — build test, bench, and demo
#   make run        — build and run the unit tests
#   make run-bench  — build and run the benchmark
#   make run-demo   — build and run the demonstration
#   make clean      — remove all build artifacts
# -----------------------------------------------------------------------------

CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS  ?=

.PHONY: all run run-bench run-demo clean

all: test bench demo

# If a recipe fails, delete the target file so a half-built .o doesn't linger
.DELETE_ON_ERROR:

# -----------------------------------------------------------------------------
# Executables
# -----------------------------------------------------------------------------

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# -----------------------------------------------------------------------------
# Object files — explicit rules for correct header dependencies
# -----------------------------------------------------------------------------

test.o: test.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ $<

bench.o: bench.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

demo.o: demo.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ $<

ulda.o: ulda.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

puzzles.o: puzzles.c puzzles.h ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

# -----------------------------------------------------------------------------
# Run targets
# -----------------------------------------------------------------------------

run: test
	./test

run-bench: bench
	./bench

run-demo: demo
	./demo

# -----------------------------------------------------------------------------
# Clean
# -----------------------------------------------------------------------------

clean:
	rm -f *.o test bench demo
