CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
LDFLAGS ?=

.PHONY: all test clean

all: test

test: test.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^

test.o: test.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

ulda.o: ulda.c ulda.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: test
	./test

clean:
	rm -f *.o test
