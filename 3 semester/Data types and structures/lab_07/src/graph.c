#include "inc/graph.h"

graph_t* create_from_file(FILE* file) {
    graph_t* graph = calloc(sizeof(*graph), 1);

    if (fscanf(file, "%zu", &graph->num) != 1 || graph->num == 0) {
        free_graph(graph);
        return NULL;
    }
    size_t n = graph->num;
    graph->adjacency_matrix = init_matrix(n, n);

    size_t a, b;
    while (1) {
        int rc = fscanf(file, "%zu->%zu", &a, &b);
        if (rc != 2) {
        if (rc < 0) {
            break;
        } else {
            free_graph(graph);
            return NULL;
        }
        }

        if (a < 1 || b < 1 || a > n || b > n) {
        free_graph(graph);
        return NULL;
        }
        graph->adjacency_matrix->data[a - 1][b - 1] = 1;
    }

    generate_reachability_matrix(graph);

    return graph;
}

int generate_reachability_matrix(graph_t* graph) {
    size_t n = graph->num;
    matrix_t* result = copy_matrix(graph->adjacency_matrix);
    matrix_t* temp = copy_matrix(graph->adjacency_matrix);

    for (size_t i = 0; i < n - 1; i++) {
        matrix_t* current = mul(temp, graph->adjacency_matrix);
        free_matrix(temp);
        temp = current;

        matrix_t* result_sum = sum(result, temp);
        free_matrix(result);
        result = result_sum;
    }

    graph->reachability = result;

    return 0;
}

void free_graph(graph_t* graph) {
    if (!graph) return;

    free_matrix(graph->adjacency_matrix);
    free_matrix(graph->reachability);

    free(graph);
}

int export_dot(FILE* file, graph_t* graph) {
    fprintf(file, "digraph graphname {\n");
    for (size_t i = 0; i < graph->num; i++) fprintf(file, "\"%zu\";\n", i + 1);

    for (size_t i = 0; i < graph->num; i++)
        for (size_t j = 0; j < graph->num; j++)
        if (graph->adjacency_matrix->data[i][j])
            fprintf(file, "\"%zu\" -> \"%zu\";\n", i + 1, j + 1);
    fprintf(file, "}");

    return 0;
}

int export_dot_reachability(FILE* file, graph_t* graph, size_t point) {
    fprintf(file, "digraph graphname {\n");

    for (size_t i = 0; i < graph->num; i++)
        if (graph->reachability->data[point][i])
        fprintf(file, "\"%zu\" [color=green];\n", i + 1);
        else
        fprintf(file, "\"%zu\" [color=red];\n", i + 1);

    for (size_t i = 0; i < graph->num; i++)
        for (size_t j = 0; j < graph->num; j++)
        if (graph->adjacency_matrix->data[i][j])
            fprintf(file, "\"%zu\" -> \"%zu\";\n", i + 1, j + 1);
    fprintf(file, "}");

    return 0;
}
