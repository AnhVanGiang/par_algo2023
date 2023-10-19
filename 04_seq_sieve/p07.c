#include "bspedupack.h"

/*  This program generates al prime numbers up to a certain bound n,for n>=2.
    It works as follows. Start with the integers from 2 to n.
    The number 2 is a prime; cross out all larger multiples of 2.
    The smallest remaining number, 3, is a prime;
    cross out all larger multiples of 3.
    The smallest remaining number, 5, is a prime, etc.
    The output should equal ....
*/

static long P; // number of processors requested
static long N; // global vector length
static long cross_out_count = 0; // Initialize the counter for cross-out operat$

void bspsieve()
{
    bsp_begin(P);
    long p = bsp_nprocs();
    long n = N;
    long s = bsp_pid();
    if (s == 0) {
        if (n < 2)
            bsp_abort("Error in input: n should be at least 2");
    }

    /*  Compute number of local components of processor s
    for vector of length n distributed cyclically over p processors.
    Also useful for block distribution with ceil (n/p) components if
    s < (n mod p) , floor (n/p) components otherwise .
    */
    long nl = nloc(p, s, n);

    /* Allocate and initialize the is_prime vector using vecalloci */
    char *is_prime = (char *)vecalloci(nl);

    // Initialize the is_prime array
    for (long i = 0; i < nl; i++) {
        long number = s * nl + i + 2;  // Start from 2 because 0 and 1 are not $
        is_prime[i] = 1;  // Assume all numbers are prime initially
    }

    // Perform the Sieve of Eratosthenes algorithm
    for (long i = 2; i * i <= n; i++) {
        if (is_prime[i - 2]) {
            for (long j = (i * i - 2); j < nl; j += i) {
                if (is_prime[j]) {
                    is_prime[j] = 0;  // Mark multiples of prime numbers as not$
                    cross_out_count++;
                }
            }
        }
    }

    bsp_sync();

    // Print prime numbers
    for (long i = 0; i < nl; i++) {
        if ((i<100 || i>n-100) && is_prime[i]) {
            printf("Proc %ld: %ld is prime\n", s, s * nl + i + 2);
        }
    }

    printf("Proc %ld: Total cross-out operations: %ld\n", s, cross_out_count);

    bsp_end();
    free(is_prime);
}

int main(int argc, char **argv) {
    bsp_init(bspsieve, argc, argv);

    P = bsp_nprocs();
    if (argc > 1) P = atol(argv[1]);
    if (P > bsp_nprocs()) {
        printf("Sorry, only %u processors available.\n", bsp_nprocs());
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    N = 1000;
    if (argc > 2) N = atol(argv[2]);

    /* SPMD part */
    bspsieve();

    // Calculate and print the estimated total operations
    double estimated_operations = (1-1/log(N))*(N-2);
    printf("Estimated total operations: %.2lf\n", estimated_operations);

    exit(EXIT_SUCCESS);
}
