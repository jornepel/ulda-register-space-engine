CC      ?= cc
CFLAGS  ?= -O2 -g -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS  ?=

.PHONY: all run run-bench run-demo clean

all: test bench

.DELETE_ON_ERROR:

OBJS = test.o bench.o ulda.o puzzles.o demo.o

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Build any .o from matching .c (header deps below override this).
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Header dependency tree — one line per object that has extra deps.
test.o:    ulda.h puzzles.h
bench.o:   ulda.h
ulda.o:    ulda.h
puzzles.o: ulda.h puzzles.h
demo.o:    ulda.h puzzles.h    # verify demo.c actually includes puzzles.h

run: test
	./test

run-bench: bench
	./bench

run-demo: demo
	./demo

clean:
	rm -f *.o test bench demo
