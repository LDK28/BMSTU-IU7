#include "./inc/matrix.h"

matrix_t *init_matrix(size_t rows, size_t cols) {
    matrix_t *matrix = malloc(sizeof(matrix_t));

    matrix->cols = cols;
    matrix->rows = rows;

    matrix->data = calloc(
        sizeof(matrix_type_t *) * rows + sizeof(matrix_type_t) * rows * cols, 1);

    for (size_t i = 0; i < rows; i++)
        matrix->data[i] = (matrix_type_t *)(matrix->data + rows) + cols * i;

    return matrix;
}

matrix_t *copy_matrix(matrix_t *source) {
    matrix_t *destination = init_matrix(source->rows, source->cols);

    for (size_t i = 0; i < source->rows; i++)
        for (size_t j = 0; j < source->cols; j++)
        destination->data[i][j] = source->data[i][j];

    return destination;
}

void free_matrix(matrix_t *matrix) {
    if (!matrix) return;
    free(matrix->data);
    free(matrix);
}

matrix_t *sum(const matrix_t *l, const matrix_t *r) {
    if (!l || !r) return NULL;

    if (l->rows != r->rows || l->cols != r->cols) return NULL;

    matrix_t *new_matrix = init_matrix(l->rows, l->cols);

    if (new_matrix == NULL) return NULL;

    for (size_t j = 0; j < l->rows; j++)
        for (size_t i = 0; i < l->cols; i++)
        new_matrix->data[j][i] = l->data[j][i] + r->data[j][i];

    return new_matrix;
}

matrix_t *mul(const matrix_t *left, const matrix_t *right) {
    if (!left || !right) return NULL;
    if (left->cols != right->rows) return NULL;

    matrix_t *new_matrix = init_matrix(left->rows, right->cols);

    if (new_matrix == NULL) return NULL;

    for (size_t i = 0; i < left->rows; i++)
        for (size_t k = 0; k < right->rows; k++)
        for (size_t j = 0; j < right->cols; j++)
            new_matrix->data[i][j] += left->data[i][k] * right->data[k][j];

    return new_matrix;
}
