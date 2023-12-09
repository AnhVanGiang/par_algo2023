#include "csr_ops.h"
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include <string.h>
#include <stdio.h>

void createDiagFromCSR(CSRGraph graph, long N, long *D) {
    for (long i = 0; i < N; i++) {
        long outlinks = graph.row_ptr[i + 1] - graph.row_ptr[i];
        D[i] = (outlinks > 0) ? 1.0 / outlinks : 0.0; 
    }
}

CSRGraph generateCSRGraph(int N) {
    CSRGraph graph;
    graph.row_ptr = (long *)malloc((N + 1) * sizeof(long));
    graph.col_ind = (long *)malloc(N * N * sizeof(long)); // Over-allocate initially
    graph.total_values = 0;

    srand((unsigned) time(NULL));

    graph.row_ptr[0] = 0;
    for (long i = 0; i < N; i++) {
        graph.row_ptr[i + 1] = graph.row_ptr[i];
        long num_links = rand() % 10 + 1; // Each node will point to 1-10 other nodes
        for (long j = 0; j < num_links; j++) {
            long col_index;
            do {
                col_index = rand() % N;
            } while (col_index == i); // Ensure we do not have self-links
            // Check if this edge already exists
            int edge_exists = 0;
            for (long k = graph.row_ptr[i]; k < graph.row_ptr[i + 1]; k++) {
                if (graph.col_ind[k] == col_index) {
                    edge_exists = 1;
                    break;
                }
            }
            if (!edge_exists) {
                graph.col_ind[graph.row_ptr[i + 1]] = col_index;
                graph.row_ptr[i + 1]++;
            }
        }
    }

    // Reallocate col_ind to the correct size
    graph.col_ind = (long *)realloc(graph.col_ind, graph.row_ptr[N] * sizeof(long));
    graph.total_values = graph.row_ptr[N]; // Update total_values to the actual number of edges

    return graph;
}

void CSRToColumnStocMatrix(CSRGraph graph, long N, long **M) {
    long *D = (long *)malloc(N * sizeof(long));
    
    // Initialize the stochastic matrix M to zero
    for (long i = 0; i < N; i++) {
        M[i] = (long *)calloc(N, sizeof(long));
    }
    
    // Create the diagonal from the CSR graph
    createDiagFromCSR(graph, N, D);
    
    // Populate the stochastic matrix M
    for (long i = 0; i < N; i++) {
        for (long j = graph.row_ptr[i]; j < graph.row_ptr[i + 1]; j++) {
            long col = graph.col_ind[j];
            M[col][i] = D[i];
        }
    }
    
    free(D);
}

long getCSRIndex(long i, long j, long N, CSRGraph graph) {
    for (long k = graph.row_ptr[j]; k < graph.row_ptr[j + 1]; k++) {
        if (graph.col_ind[k] == i) {
            return k;
        }
    }
    return -1;
}

CSRGraph generateSampleCSRGraph() {
    CSRGraph graph;
    int N = 4; // Number of nodes, updated to reflect the matrix size in the image
    graph.total_values = 5; // Number of non-zero edges, updated to reflect the matrix in the image
    graph.row_ptr = (long *)malloc((N + 1) * sizeof(long));
    graph.col_ind = (long *)malloc(graph.total_values * sizeof(long));

    // Manually setting the col_ptr
    graph.row_ptr[0] = 0; 
    graph.row_ptr[1] = 1; 
    graph.row_ptr[2] = 3; 
    graph.row_ptr[3] = 4; 
    graph.row_ptr[4] = 5; 

    // Manually setting the row indices for each non-zero edge
    graph.col_ind[0] = 1; 
    graph.col_ind[1] = 0; 
    graph.col_ind[2] = 2; 
    graph.col_ind[3] = 2; 
    graph.col_ind[4] = 3; 

    return graph;
}


void generateIsVector(CSRGraph graph, long processor_id, long total_processors, long N, long *Is_size, long *Is) {
    // long* rows_processed = (long*)calloc(N, sizeof(long)); // To keep track of rows that have been processed
    *Is_size = 0;

    // Iterate over the rows
    for (long i = 0; i < N; ++i) {
        // Check if the row has been processed
        for (long j = graph.row_ptr[i]; j < graph.row_ptr[i + 1]; ++j) {
            long col_ind = graph.col_ind[j];
            printf("col_ind: %ld i %ld \n", col_ind, i);
            // Check if the row belongs to the processor
            long proc = (long) getProcessorForMatrixElement(i, col_ind, N, total_processors);
            if (proc == processor_id) {
                Is[*Is_size] = i;
                *Is_size += 1;
                printf("Added \n");
                break;
            }
        } 
    }
}

void generateJsVector(CSRGraph graph, long processor_id, long total_processors, long N, long *Js_size, long *Js) {
    long* cols_processed = (long*)calloc(N, sizeof(long)); // To keep track of rows that have been processed
    *Js_size = 0;

    // Iterate over the rows
    for (long i = 0; i < N; ++i) {
        // Check if the row has been processed
        for (long j = graph.row_ptr[i]; j < graph.row_ptr[i + 1]; ++j) {
            long col_ind = graph.col_ind[j];
            if (cols_processed[col_ind] == 0) {
                printf("col_ind: %ld i %ld \n", col_ind, i);
                // Check if the row belongs to the processor
                long proc = (long) getProcessorForMatrixElement(i, col_ind, N, total_processors);
                if (proc == processor_id) {
                    Js[*Js_size] = col_ind;
                    *Js_size += 1;
                    printf("Added \n");
                    cols_processed[col_ind] = 1;
                }
        } 
    }
    }
    free(cols_processed);
}




