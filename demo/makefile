demo: demo.o ulda.o puzzles.o
	$(CC) $(LDFLAGS) -o $@ $^

demo.o: demo.c ulda.h puzzles.h
	$(CC) $(CFLAGS) -c -o $@ $<

run-demo: demo
	./demo
