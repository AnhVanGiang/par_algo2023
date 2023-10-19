#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void bspsieve() {
    int n;
    scanf("%d", &n); // Read the limit

    bool* primes = (bool*) malloc((n + 1) * sizeof(bool));
    for (int i = 0; i <= n; i++) {
        primes[i] = true; // initialize all to true (potentially prime)
    }

    primes[0] = primes[1] = false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += i) {
                primes[j] = false; // mark multiples of i as non-prime
            }
        }
    }

    // Print the primes
    if (n<=1000)
    for (int i = 2; i <= n; i++) {
        if (primes[i]) {
            printf("Found prime: %d\n", i);
        }
    }

    free(primes);
}

int main() {
    bspsieve();
    return 0;
}
