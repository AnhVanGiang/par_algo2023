#include <stdio.h>
#include <stdlib.h>
#include <math.h>


long n = 100;
const int n_max = __INT_MAX__;

__int8_t* is_composite;



void setup() {
    is_composite = (__int8_t*) calloc (n+1, sizeof(__int8_t));
    is_composite[0] = 1;
    is_composite[1] = 1;
}

void cleanup() {
    free(is_composite);
}

void print_primes() {
    for (long i = 0; i < n; ++i) {
        if (is_composite[i] == 0) {
            printf("%ld,", i);
        }
    }
    printf("\n");
}

long count_primes() {
    long res = 0;
    for (long i = 0; i < n; ++i) {
        if (is_composite[i] == 0) {
            res += 1;
        }
    }
    return res;
}

void sieve_single(long x) {
    long i = x*x;
    while ( i <= n ) {
        is_composite[i] = 1;
        i += x;
    }
}

void sieve(long start) {
    long next = start;
    long sqrtn = sqrt(n);

    while(next <= sqrtn) {
        sieve_single(next);
        do {
            next += 1;
        } while (next <= sqrtn && is_composite[next]);
    }
}



int main(int argc, char **argv){
    setup();
    sieve(2);
    printf("Found %ld primes\n", count_primes());
    print_primes();
    cleanup();
}