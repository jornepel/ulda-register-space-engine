CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

all: ulda_test

ulda_test: main.c ulda.c ulda.h
	$(CC) $(CFLAGS) -o ulda_test main.c ulda.c

run: ulda_test
	./ulda_test

clean:
	rm -f ulda_test

.PHONY: all run clean
