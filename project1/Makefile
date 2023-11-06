CFLAGS = -O3 -march=native

default: bsp

bsp: parallel_sieve.x

parallel_sieve.x: parallel_sieve.c bspedupack.c
	bspcc $(CFLAGS) -g -o parallel_sieve $< bspedupack.c -lm

clean:
	-rm *.o *.x

