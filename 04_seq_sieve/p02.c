#include <stdio.h>
#include <time.h>
#include <stdbool.h>


double sieve(long n, bool print) { //Returns the computation time (excluding initialization of the array)
	// Initialize array
	long arr[n-1];
	for (long i=0; i<n-1; i++)
		arr[i] = i+2;

	//for (long i=0; i<n-1; i++)
	//	printf("%ld ",arr[i]); fflush(stdout);

	clock_t begin = clock();

	long n_removed = 0; //Keep track of the number of removed (non-prime) integers
	for (long i=0; i<n-1-n_removed; i++) {
		long k = arr[i];
		long j= i+1;
		while (j < n-1-n_removed) {
			if ( arr[j] % k == 0 ) {
				n_removed++;
				//printf("Removed the number %ld\n",arr[j]); fflush(stdout);
				for (long m=j; m <n-1-n_removed;m++)
					arr[m] = arr[m+1];
			}
			else
				j++;
		}
	}

	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;

	if (print) {
		printf("In %f seconds, we found %ld prime numbers less than or equal to %ld:\n", n-n_removed-1,n); fflush(stdout);
		for (long i=0; i<n-1-n_removed; i++)
			printf("%ld ",arr[i]); fflush(stdout);
	}
	return time_spent;
}

int main() {
	long n_array[] = {100,200,500,1000,2000,5000,10000,20000,50000,100000,200000};
	for (int i=0; i< sizeof(n_array)/sizeof(n_array[0]); i++) {
		double result = sieve(n_array[i], false);
		printf("Algorithm completed in %f seconds for n=%ld.\n",result,n_array[i]);
	}
	return 0;
}
