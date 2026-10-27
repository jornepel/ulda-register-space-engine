CC      ?= cc
CFLAGS  ?= -O2 -g -Wall -Wextra -std=c11
LDFLAGS ?=
LDLIBS  ?=

.PHONY: all run run-bench run-demo clean lib

all: test bench

.DELETE_ON_ERROR:

OBJS = test.o bench.o ulda.o puzzles.o demo.o

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# ---- Shared library for Python (ctypes) ----
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    SHARED_EXT   = dylib
    SHARED_FLAGS = -dynamiclib
else
    SHARED_EXT   = so
    SHARED_FLAGS = -shared
endif

libulda.$(SHARED_EXT): ulda_shim.o ulda.o
	$(CC) $(SHARED_FLAGS) -o $@ $^

# ulda_shim.o needs -fPIC because it goes into the shared lib.
ulda_shim.o: ulda_shim.c ulda.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# ulda.o is used by both executables and the shared lib → -fPIC is safe.
ulda.o: ulda.c ulda.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

lib: libulda.$(SHARED_EXT)

# Build any .o from matching .c (header deps below override this).
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Header dependency tree — one line per object that has extra deps.
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

.PHONY: print-cflags
print-cflags:
	@echo '$(CFLAGS)'

clean:
	rm -f *.o test bench demo libulda.so libulda.dylib
