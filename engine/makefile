CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
LDFLAGS ?=

.PHONY: all run run-bench clean

all: test bench

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

test.o: test.c ulda.h puzzles.h
puzzles.o: puzzles.c puzzles.h ulda.h

run: test
	./test

run-bench: bench
	./bench

clean:
	rm -f *.o test bench
