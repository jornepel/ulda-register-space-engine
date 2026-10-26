make
CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS  ?=

.PHONY: all run run-bench run-demo clean

all: test bench

.DELETE_ON_ERROR:

# Define all objects cleanly
OBJS = test.o bench.o ulda.o puzzles.o demo.o

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Static pattern rule - now correctly referencing the comprehensive OBJS variable
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Explicit header dependency trees (relying cleanly on the pattern rule above)
test.o:    ulda.h puzzles.h
bench.o:   ulda.h
ulda.o:    ulda.h
puzzles.o: puzzles.h ulda.h
demo.o:    ulda.h puzzles.h

run: test
	./test

run-bench: bench
	./bench

run-demo: demo
	./demo

clean:
	rm -f *.o test bench demo
