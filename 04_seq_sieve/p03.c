#include <stdio.h>
#include <stdbool.h>

void primeMod(int n, int i, int j, int q);
void primeSquare(int n, int i, int j, int q);

int main()
{
    int n; int i; int j; int q;
    printf("Enter a value :");
    scanf("%d", &n);
    primeSquare(n, i, j, q);
    return 0;
}

void primeMod(int n, int i, int j, int q){
    int primes[n], prime, alpha = 0;
    for (i = 0; i<n; i++){
        primes [i] = i+1;
    }
    primes[0] = 0;

    for (q = 2; q <= n; q++){
        prime = q;
        for (j = 0; j<=n;++j){
            if ((j!=prime)&&(j%prime == 0)){
                primes[j-1]=0;
            }
        }
    }

    printf("Result array:\n");
    for (i = 0; i<n; i++){
        if (primes[i] != 0){
            printf("%d\n",primes[j]);
        }
    }
}

void primeSquare(int n, int i, int j, int q){
    int s;
    
    bool primes[n];
    for (i = 0; i <= n; ++i){
        primes[i] = true;
    }

    for (j = 2; j*j <= n; ++j){
        if (primes[j] == true){
            for (q = j*j; q <= n; q+=j){
                primes[q] = false;
            }  
        }     
    }

    printf("Result array: \n");
    for (s = 2; s <= n; ++s){
        if (s<=100 || s>n-100){
        if (primes[s] == true){
            printf("%d ", s);
        }
      }
    }
}
