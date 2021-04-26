#ifndef INC_GRAPH_H_
#define INC_GRAPH_H_
#include <stdio.h>
#include <stdlib.h>

#include "inc/matrix.h"

typedef struct graph
{
    size_t num;
    matrix_t* adjacency_matrix;
    matrix_t* reachability;
} graph_t;

graph_t* create_from_file(FILE* file);

int generate_reachability_matrix(graph_t* graph);

void free_graph(graph_t* graph);

int export_dot(FILE* file, graph_t* graph);
int export_dot_reachability(FILE* file, graph_t* graph, size_t point);

#endif  // INC_GRAPH_H_
