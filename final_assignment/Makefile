CC=bspcc
CFLAGS=-I. -O3 -march=native

DEPS = graph.h sequential_pr.h math_ops.h matrix_vector_ops.h csr_ops.h utilities.h bspedupack.h
OBJ = main.o math_ops.o matrix_vector_ops.o csr_ops.o utilities.o sequential_pr.o bspedupack.o

# Add rule to compile bspedupack.c
bspedupack.o: bspedupack.c bspedupack.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Pattern rule for object files, depends on DEPS
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Link the program
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

# Phony targets for clean and rebuild
.PHONY: clean rebuild

clean:
	rm -f $(OBJ) main

rebuild: clean main