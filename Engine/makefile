CC      ?= cc
CFLAGS  ?= -O3 -march=native -flto -fomit-frame-pointer -Wall -Wextra -std=c11
LDFLAGS ?= -flto
LDLIBS  ?=

.PHONY: all run run-bench run-demo run-cosmos run-tensor clean lib print-cflags

# All 5 core executables build sequentially under one banner
all: test bench demo cosmos tensor

.DELETE_ON_ERROR:

# Removed tensor.o from here so it stops looking for tensor.c
OBJS = test.o bench.o puzzles.o demo.o

test: test.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

bench: bench.o ulda.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
cosmos: cosmos.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

tensor: tensor.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Explicit compilation match for ulda_cosmos.c
cosmos.o: ulda_cosmos.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ ulda_cosmos.c

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

# Explicit, position-independent rule for your tensor cross-talk module
tensor.o: ulda_tensor.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

lib: libulda.$(SHARED_EXT)

# Build standard matching object components
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Header dependency tree
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

run-cosmos: cosmos
	./cosmos

run-tensor: tensor
	./tensor

.PHONY: print-cflags
print-cflags:
	@echo '$(CFLAGS)'

clean:
	rm -f *.o test test.exe bench bench.exe demo demo.exe cosmos cosmos.exe tensor tensor.exe libulda.so libulda.dylib
