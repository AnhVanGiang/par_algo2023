#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    long *row_ptr;
    long *col_ind;
    long total_values;
} CSRGraph;


typedef struct {
    int x;
    int y;
} coordinate;

typedef struct {
    long start_index;
    long length;
} ProcessorInfo;


#endif 