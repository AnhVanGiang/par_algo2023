#ifndef UTILITIES_H
#define UTILITIES_H

#include "graph.h"

void makeStochasticVector(double *vector, int size);
void addVectors(double *vector1, double *vector2, double *result, int N);
void subVectors(double *vector1, double *vector2, double *result, int N);
void addVectorWithConstant(double *vector, double constant, int N);
void normalizeVector(double *vector, int N);
void inverseDiagonalMatrix(double *D, int N, double *result);
coordinate getProcessorCoordinates(int procNum, int totalProcs); 
long nnodes(long s, long N, long P);
int getProcessorForMatrixElement(int i, int j, int N, int totalProcs);
long getStartIndex(long s, long N, long P);
long getProcIdForIndex(long index, long vector_length, long num_procs);

#endif 