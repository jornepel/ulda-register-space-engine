# ULDA-X28 — Makefile

CC      = gcc
CFLAGS  = -O2 -Wall

# The test target — this is what you run
test: ulda.c test.c
	$(CC) $(CFLAGS) ulda.c test.c -o ulda_test
	./ulda_test

# The bare-metal target — no OS, no stdlib
bare: ulda.c
	$(CC) -nostdlib -ffreestanding -O2 -c ulda.c -o ulda.o

clean:
	rm -f ulda.o ulda_test

.PHONY: test bare clean
