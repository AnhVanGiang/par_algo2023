#ifndef CSR_OPS_H
#define CSR_OPS_H

#include "graph.h"

void createDiagFromCSR(CSRGraph graph, long N, long *D);
CSRGraph generateCSRGraph(int N);
void CSRToColumnStocMatrix(CSRGraph graph, long N, long **M);
CSRGraph generateSampleCSRGraph();
long getCSRIndex(long i, long j, long N, CSRGraph graph);
void generateIsVector(CSRGraph graph, long processor_id, long total_processors, long N, long *Is_size, long *Is);
void generateJsVector(CSRGraph graph, long processor_id, long total_processors, long N, long *Js_size, long *Js);

#endif