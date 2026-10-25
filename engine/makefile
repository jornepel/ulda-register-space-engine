CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS  ?=

.PHONY: all run run-bench run-demo clean

all: test bench
# demo: enable once demo.c exists

.DELETE_ON_ERROR:

OBJS = test.o bench.o ulda.o puzzles.o

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# One recipe, applied only to listed objects
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Per-object header deps (no recipe — the rule above supplies it)
test.o:    ulda.h puzzles.h
bench.o:   ulda.h
ulda.o:    ulda.h
puzzles.o: puzzles.h ulda.h

run: test
	./test

run-bench: bench
	./bench

run-demo: demo
	./demo

clean:
	rm -f *.o test bench demo
