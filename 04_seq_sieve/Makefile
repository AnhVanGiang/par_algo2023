
BSPCC=/home/jonas/src/MulticoreBSP-for-C/tools/bspcc


all: p01.x p02.x p03.x p04.x p05.x p06.x p07.x  p_jonas.x

%.x: %.c
	gcc -O3 -o $@ $< -lm

p06.x: p06.c bspedupack.c bspedupack.h
	${BSPCC} -O3 -o $@ $< bspedupack.c -lm

p_jonas.x: p_jonas.c
	mpicc -O3 -o $@ $< -lm

clean:
	-rm *.x
