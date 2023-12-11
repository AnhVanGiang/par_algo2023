#ifndef SEQUENTIAL_PR_H
#define SEQUENTIAL_PR_H

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void pGDr(double p, double **G, double *D, double *input_vector, double *result_vector, int N);
long solvePageRank(double *u, double p, double *D, CSRGraph G, int N, double *r);

#endif
