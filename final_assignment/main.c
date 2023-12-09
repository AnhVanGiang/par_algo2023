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

// int getProcessorNumber(coordinate coord, int M) {
//     return coord.y * M + coord.x;
// }

long *D;

static long P;

void computeD(long *row_ptr, long N, long P, long start_index, long n, long *D) {
    long s = bsp_pid(); 

    // Allocate the full D vector on each processor
    long *d = vecalloci(n);
    long *D_ = vecalloci(N);
    bsp_push_reg(D_, N * sizeof(long));

    // Share the starting index and number of rows with all processors
    long *start_indices = vecalloci(P);
    long *row_counts = vecalloci(P);
    bsp_push_reg(start_indices, P * sizeof(long));
    bsp_push_reg(row_counts, P * sizeof(long));

    bsp_sync(); // Synchronization point

    // Broadcast the starting index and row counts to all processors
    for (long p = 0; p < P; p++) {
        bsp_put(p, &start_index, start_indices, s * sizeof(long), sizeof(long));
        bsp_put(p, &n, row_counts, s * sizeof(long), sizeof(long));

    }
    bsp_sync(); // Synchronization point

    // Local computation of D
    for (long i = 0; i < n; i++) {
        d[i] = row_ptr[i + 1] - row_ptr[i] == 0 ? 1 : (row_ptr[i + 1] - row_ptr[i]);
    }

    // Now we need to communicate the computed values of D to all processors
    // Since each processor knows the starting indices and row counts, they can put the data correctly
    for (long p = 0; p < P; p++) {
        // printf("Processor %ld has start index %ld and row count %ld\n", p, start_indices[p], row_counts[p]);
        bsp_put(p, d, D_, start_indices[s] * sizeof(long), row_counts[s] * sizeof(long));
    }

    bsp_sync();

    for (long i = 0; i < N; i++) {
        D[i] = D_[i];
    }

    bsp_pop_reg(start_indices);
    bsp_pop_reg(row_counts);
    vecfreei(start_indices);
    vecfreei(row_counts);
    vecfreei(d);
    vecfreei(D_);
}




void bspPar() {
    CSRGraph graph = generateSampleCSRGraph();
    long N = 4;
    bsp_begin(P);
    long P = bsp_nprocs(); // Number of processors
    long s = bsp_pid();    // Processor ID

    long *row_ptr = graph.row_ptr; // Pointer to the row_ptr array
    long start_index = getStartIndex(s, N, P); // Starting index of the local block
    long n = nnodes(s, N, P); // Number of nodes in the local block
    D = vecalloci(N); // Allocate the full D vector on each processor

    long *Is = vecalloci(N); // Allocate the local Is vector
    long Is_size = 0; // Size of the local Is vector

    long *Js = vecalloci(N); // Allocate the local Js vector

    long *row_ptr_local = vecalloci(n + 1);


    for (long i = 0; i < n + 1; i++) {
        row_ptr_local[i] = row_ptr[start_index + i];
    }

    bsp_sync(); // Synchronization point

    // Compute the local D vector
    computeD(row_ptr_local, N, P, start_index, n, D);

    bsp_sync(); // Synchronization point
    
    bsp_end();
}

int main(int argc, char **argv) {
    bsp_init(bspComputeD, argc, argv);

    P = bsp_nprocs(); // Set the number of processors
    if (argc > 1) P = atol(argv[1]);
    if (P > bsp_nprocs()){
        printf("Sorry, only %ld processors available.\n", bsp_nprocs());
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    long N = 4; // Set the global number of nodes in the graph
    if (argc > 2) N = atol(argv[2]);

    CSRGraph graph = generateSampleCSRGraph();

    // Initialize CSR graph

    // SPMD part to compute D
    bspComputeD(graph, N);

    for (long i = 0; i < N; i++) {
        printf("D[%ld] = %ld\n", i, D[i]);
    }

    // Sequential part (if necessary)
    // Deallocate CSR graph (not provided, assumed to exist)
    
    exit(EXIT_SUCCESS);
}
