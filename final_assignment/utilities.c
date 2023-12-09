#include "utilities.h"
#include <math.h>
#include "graph.h"

void makeStochasticVector(double *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = 1.0 / size;
    }
}

void addVectors(double *vector1, double *vector2, double *result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = vector1[i] + vector2[i];
    }
}

void subVectors(double *vector1, double *vector2, double *result, int N) {
    for (int i = 0; i < N; i++) {
        result[i] = vector1[i] - vector2[i];
    }
}

long getProcIdForIndex(long index, long vector_length, long num_procs) {
    // Calculate the number of elements per processor.
    long elements_per_proc = vector_length / num_procs;
    
    // The last processor may have more elements if the vector length
    // is not evenly divisible by the number of processors.
    long remaining_elements = vector_length % num_procs;
    
    // If the index is within the range that has an evenly distributed number of elements
    if (index < elements_per_proc * num_procs) {
        return index / elements_per_proc;
    } else {
        // If the index is in the range of the remaining elements,
        // it belongs to the last processor.
        return num_procs - 1;
    }
}

void addVectorWithConstant(double *vector, double constant, int N) {
    for (int i = 0; i < N; i++) {
        vector[i] += constant;
    }
}

void normalizeVector(double *vector, int N) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += vector[i];
    }
    for (int i = 0; i < N; i++) {
        vector[i] /= sum;
    }
}

void inverseDiagonalMatrix(double *D, int N, double *result) {
    for (int i = 0; i < N; i++) {
        result[i] = 1.0 / D[i];
    }
}

coordinate getProcessorCoordinates(int procNum, int totalProcs) {
    int gridSize = (int)sqrt(totalProcs);
    coordinate coord;
    coord.x = procNum % gridSize;
    coord.y = procNum / gridSize;
    return coord;
}

long nnodes(long s, long N, long P) {
    long base = N / P;
    long extra = N % P;

    if (s < extra) {
        return base + 1;
    } else {
        return base;
    }
}

long getStartIndex(long s, long N, long P) {
    // For the first processor
    if (s == 0) {
        return 0;
    }
    
    // Calculate the base size of chunks
    long baseSize = N / P;

    // Distribute the remaining elements
    long extra = N % P;

    // Start index calculation
    if (s <= extra) {
        return s * (baseSize + 1);
    } else {
        return extra * (baseSize + 1) + (s - extra) * baseSize;
    }
}

int getProcessorForMatrixElement(int i, int j, int N, int totalProcs) {
    if (i == j) {
        return getProcIdForIndex(i, N, totalProcs);
    }
    int block_row = getProcIdForIndex(i, N, totalProcs);
    int block_col = getProcIdForIndex(j, N, totalProcs);

    int block_row_coord_x = getProcessorCoordinates(block_row, totalProcs).x;
    int block_col_coord_y = getProcessorCoordinates(block_col, totalProcs).y;

    int M = (int)sqrt(totalProcs);

    return block_col_coord_y * M + block_row_coord_x;
}