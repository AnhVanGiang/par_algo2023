#ifndef MATRIX_VECTOR_OPS_H
#define MATRIX_VECTOR_OPS_H

void matrixVectorMultiply(double **matrix, double *vector, double *result, int N);
void csrMatrixVectorNultiplication(CSRGraph graph, double *vector, double *result, int N);
void multiplyDiagonalMatrixByVector(double *diagonal, double *vector, double *result, int N);
void multiplyVectorByConstant(double *vector, double constant, int N);

#endif