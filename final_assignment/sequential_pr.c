#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "math_ops.h"
#include "matrix_vector_ops.h"
#include "csr_ops.h"
#include "utilities.h"
#include <math.h>
#include "bspedupack.h"
#include <string.h>

void pGDr(double p, CSRGraph G, double *D, double *input_vector, double *result_vector, int N) {
    double *intermediate = (double *)malloc(N * sizeof(double));

    multiplyDiagonalMatrixByVector(D, input_vector, intermediate, N); // D * input_vector
    csrMatrixVectorNultiplication(G, intermediate, result_vector, N); // G * (D * input_vector)
    multiplyVectorByConstant(result_vector, p, N); // p * G * (D * input_vector);

    free(intermediate);
}
long solvePageRank(double *u, double p, double *D, CSRGraph G, int N, double *r) {
    long iter = 0;
    double *e = (double *)calloc(N, sizeof(double));
    // double *r = (double *)calloc(N, sizeof(double));
    double *pgdu = (double *)malloc(N * sizeof(double));
    double *intermediate = (double *)malloc(N * sizeof(double));

    addVectorWithConstant(e, 1.0, N);

    pGDr(p, G, D, u, pgdu, N); // p * G * D^-1 * u^0
    subVectors(e, u, intermediate, N); // e - u

    addVectors(intermediate, pgdu, r, N); // (e - u) + p * G * D^-1 * u
    // printf("%f\n", L2Norm(r, N));
    while (L2Norm(r, N) >= 0.00001) {
        // printf("L2 Norm of current iter: %f\n", L2Norm(r, N));
        pGDr(p, G, D, r, intermediate, N); // p * G * D^-1 * r
        addVectors(intermediate, u, u, N); // intermediate + u^k
        memcpy(r, intermediate, N * sizeof(double)); // Update r for the next iteration
        iter++;
        // printf("L2 Norm of next iter * p: %f\n \n", p * L2Norm(r, N));
    }

    free(e);
    // free(r);
    free(pgdu);
    free(intermediate);

    return iter;
}