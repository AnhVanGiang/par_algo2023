//
//  main.c
//  Parallel_Algo
//
//  Created by XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//

// Answers Assignment:
// part a: Stop whenever the array containing numbers 2 through n is empty.
// part b: Start with an initial array containing integers 2 to n. Iterate over them starting at 2, and delete all integers that are equal to 2 or a multiple of 2. Add the prime 2 to the primes array. Continue doing this until the initial array is empty.
// part c: ??
#include <stdlib.h>
#include <stdio.h>

//Define global variables
struct Primes_result {
    int* primes_array;
    int num_primes;
};


// Make primes array function
struct Primes_result make_prime_array(int* array, int size_array){
    struct Primes_result primes;
    primes.primes_array = (int*)malloc(size_array*sizeof(int));
    primes.num_primes = 0;
    int prime = 0;
    
    while (size_array > 0) {
        prime = array[0];
        primes.num_primes++;
        primes.primes_array[primes.num_primes - 1] = prime;
        
        int product = 1;
        while (product*prime <= array[size_array-1]){
            int j = 0;
            while (j <= size_array - 1){
                if (array[j] == product*prime){
                    int k = j;
                    size_array --;
                    while (k <= size_array){
                        array[k] = array[k+1];
                        k++;
                    }
                }
                j++;
            }
            product ++;
        }
    }
    return primes;
}

// Function to construct the initial array filled with numbers 2 through n and passes it to the function where the primes are calculated
struct Primes_result seq_sieve(int n){
    struct Primes_result primes;
    int* initial_array = (int*)malloc((n-1)*sizeof(int)); // initialize empty number array

    //fill full number array
    for (int i = 2; i <= n; i++){
        initial_array[i - 2] = i;
    }
    
    primes = make_prime_array(initial_array, n-1);
    return primes;
}

int main(int argc, const char * argv[]) {
    int n;
    printf("Enter a positive integer (n): "); //Let user enter an integer n
    scanf("%d", &n);
    
    struct Primes_result primes = seq_sieve(n);
    
    //Print primes array
    printf("These are all primes from 2 through %d: ", n);
    for (int j = 0; j <= primes.num_primes - 1; j++) {
        if (j<100 || j>=primes.num_primes-100) {
        printf("%d ", primes.primes_array[j]);
        }
    }
    printf("\n");
    free(primes.primes_array); // Free memory, QUESTION: When and why is this needed?
    
    return 0;
}
