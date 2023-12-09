#include "graph.h"
#include "matrix_vector_ops.h"


void matrixVectorMultiply(double **matrix, double *vector, double *result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void csrMatrixVectorNultiplication(CSRGraph graph, double *vector, double *result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = graph.row_ptr[i]; j < graph.row_ptr[i + 1]; j++) {
            result[i] += vector[graph.col_ind[j]];
        }
    }
}

void multiplyDiagonalMatrixByVector(double *diagonal, double *vector, double *result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = diagonal[i] * vector[i];
    }
}

void multiplyVectorByConstant(double *vector, double constant, int N) {
    for (int i = 0; i < N; i++) {
        vector[i] *= constant;
    }
}