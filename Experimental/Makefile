# ============================================================================
# ULDA-X28 — Makefile (Bare-Metal Production Mode)
# Target: Freestanding Local Testing Verification
# ============================================================================

CC      = gcc
CFLAGS  = -O3 -Wall -Wextra

# The test target — Links your local ulda.c and test.c seamlessly
test: ulda.c test.c
	$(CC) $(CFLAGS) ulda.c test.c -o ulda_test
	./ulda_test

# The bare-metal target — Pure standalone silicon compilation (No OS, no stdlib)
bare: ulda.c
	$(CC) -nostdlib -ffreestanding -O3 -c ulda.c -o ulda.o

clean:
	rm -f ulda.o ulda_test

.PHONY: test bare clean
