# Shared library for ctypes (used by ulda_grid.py)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    SHARED_EXT = dylib
    SHARED_FLAGS = -dynamiclib
else
    SHARED_EXT = so
    SHARED_FLAGS = -shared
endif

libulda.$(SHARED_EXT): ulda_shim.o ulda.o
	$(CC) $(SHARED_FLAGS) -o $@ $^

ulda_shim.o: ulda_shim.c ulda.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

ulda.o: ulda.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

.PHONY: lib clean-lib
lib: libulda.$(SHARED_EXT)

clean-lib:
	rm -f libulda.so libulda.dylib ulda_shim.o
