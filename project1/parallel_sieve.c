#include "bspedupack.h"
#include <math.h>
#include <stdio.h>

static long P; // number of processors requested
static long N; // global vector length
double *primes;
long current_k = 2;

long first_multiple(long start, long end, long k) {
    if (start <= k) {
        start = k + 1;
    }
    long first_multiple = ((start - 1) / k + 1) * k;
    if (first_multiple >= end) {
        return 0; // No multiple of k within the given range
    }
    return first_multiple;
}



// Function to execute the sieve in parallel

void parallel_sieve(long start_ind, long end_ind) {
    
    long s = bsp_pid();

    // printf("Processor %lu marking non-prime at array index %lu (number %lu)\n", s, start_ind, i);

    int first_multiple_of_k = (int)(first_multiple(start_ind, end_ind, (long)current_k));

    // printf("Processor %lu has start index %lu\n", s, start_ind);
    // printf("Processor %lu has end index %lu\n", s, end_ind);
    // printf("Processor %lu has first multiple of %lu is %d at index %lu \n", s, current_k, first_multiple_of_k, first_multiple_of_k - 2);
    // printf("Processor %lu has first multiple of %lu is %d\n", s, current_k, first_multiple_of_k + start_ind - s*2);
    primes[first_multiple_of_k - 2] = 0;
    // printf("Processor %lu has marked %lu at index %lu \n", s, first_multiple_of_k, first_multiple_of_k - 2);
    bsp_sync();

    for (long i = first_multiple_of_k + (long)current_k; i < end_ind; i += (long)current_k) {
        primes[i - 2] = 0;
        // printf("Processor %lu has marked %lu at index %lu \n", s, i, i - 2);
    }


    if (s == 0) {
        for (int j = current_k - 1; j < sqrt(N) + 1; j ++) {
            if (primes[j] == 1) {
                current_k = j + 2;
                // printf("Processor %lu has updated current_k to %lu \n", s, current_k);
                break;
            }
        }
    }
}

long start_ind(long p, long s, long n) {
    long nl = nloc(p, s, n);
    return (s * nl) + 2;
}

long end_ind(long p, long s, long n) {
    long nl = nloc(p, s, n);
    return ((s + 1) * nl) + 2;
}

// // Find processor number of current_k
// long find_proc(long current_k) {
//     return floor((current_k - 2) / (N / P));
// }

void bsp_sieve() {
    bsp_begin(P);
    long s = bsp_pid();
    long p = P;
    long n = N;
    long nl = nloc(p, s, n);
    // double *primes = vecallocd(n - 1);

    for (int i = 0; i < n - 1; i++) {
        primes[i] = 1;
    }

    // bsp_sync();

    long start_index = start_ind(p, s, n);
    long end_index = end_ind(p, s, n); 

    if (s == p - 1) {
        // Adjust the end index for the last processor
        end_index = n;
    }

    // Ensure the end index doesn't exceed n
    end_index = (end_index > n) ? n : end_index;

    double time0= bsp_time();

    bsp_sync();

    long last_k = 1;

    while (current_k != last_k) {
        // printf("Current k is %lu \n", current_k);
        // printf("Last k is %lu \n", last_k);

        last_k = current_k;
        parallel_sieve(start_index, end_index);

        bsp_sync();

        // printf("%f \n", primes[2]);
    }


    bsp_sync();

    double time1= bsp_time();

    // FILE *fp;
    // fp = fopen("./output.txt", "w");

    // if (fp == NULL) {
    //     perror("Error opening file");
    // }

    if (s == 0) {
        printf("Time taken: %f \n", (time1 - time0)/100.0);
        for (long t = 0; t < n - 2; t++) {
            // printf("a %lu ", t);
            if (primes[t] == 1) {
                printf("%lu ", t + 2);
            }
        }

        // fclose(fp);
    }

    bsp_end();

}

int main(int argc, char **argv){

    bsp_init(bsp_sieve, argc, argv);

    P=bsp_nprocs();
    if (argc>1) P=atol(argv[1]);
    if (P > bsp_nprocs()){
        printf("Sorry, only %u processors available.\n",
                bsp_nprocs());
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    N=1000;
    if (argc>2) N=atol(argv[2]);
    /* SPMD part */
    primes = vecallocd(N - 1);
    bsp_sieve();

    /* Sequential part */
    exit(EXIT_SUCCESS);

} /* end main */