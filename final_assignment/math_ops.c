#include "math_ops.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

double generateRandomNumberInRange(double min, double max) {
    srand(time(NULL));
    double random_number = (double)rand() / RAND_MAX;
    return min + random_number * (max - min);
}

double L2Norm(double *vector, int N) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += vector[i] * vector[i];
    }
    return sqrt(sum);
}