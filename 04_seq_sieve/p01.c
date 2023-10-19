
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void primes(int, int[]);

// static const int n = 20;


int main() {

       enum { n = 1000 };

       // initialize list of length n
       int list_of_primes[n];
       //list_of_primes[0] = 0;

       primes(n, list_of_primes);

       return 0;

}


void primes(int n, int primes[]) {

       // make list full of all numbers up to n
       // index 0 heeft getal 1!!
       for (int k = 0; k < n; k++) {
             primes[k] = k+1;
             // printf("%d\n", primes[k]);
       }

       /*for (int k = 0; k <= n; k++) {
       printf("index %d with value %d\n", k, primes[k]);
       }*/

       // filter primes
       for (int i = 2; i < sqrt(n); i++) {

             // printf("i: %d\n", i);

             for (int k = i + i; k <= n; k = k + i) {

                    // printf("k: %d\n", k);

                    int temp = k;
                    // printf("temp: %d\n", temp);
                    primes[temp - 1] = -1;

             }

             // printf("%d\n", primes[i]);

       }

       // printf("primeslist:\n");
       for (int k = 1; k < n; k++) {

             //printf("%d", k);

             //printf("%d", sizeof(primes));
             //printf("%d\n", primes[k - 1]);
             if (primes[k] <= 0) {
                    continue;
             }
             else {
                    printf("%d\n", primes[k]);
             }
       
       }
}
