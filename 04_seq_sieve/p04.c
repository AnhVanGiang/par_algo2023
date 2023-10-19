#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    printf("Please enter a number: ");
    int n;

    scanf("%d", &n);

    int ops_counter = 0;

    int* arr;
    arr = (int*)malloc(sizeof(int) * n);

    arr[0] = 0;
    arr[1] = 0;

    for (int i = 2; i < n + 1; ++i) {
        arr[i] = 1;
    }
    for (int i = 0; i <= sqrt(n); i++) {
        if (arr[i] == 1) {
            for (int j = i * i; j < n; j += i) {
                arr[j] = 0;
                ops_counter++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i<100 || i>=n-100)
        if (arr[i] == 1) {
            printf("%d ", i);
        }
    }

    printf("The total number of cross-out operations is %d", ops_counter);

    float e = 0;
    for (int x = 3; x <= floor(sqrt(n)); x++) {
        e = e + 1 / log(x) * (floor((n - x ^ 2) / x) + 1);
    }

    printf("The estimate of cross-out operations is %f", e);
}

