#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

#include <stdlib.h>
#include <time.h>

#define MATRIX_TYPE_SPECIF "d"
typedef int matrix_type_t;

typedef struct matrix
{
    size_t rows;
    size_t cols;
    matrix_type_t **data;
} matrix_t;

matrix_t *init_matrix(size_t rows, size_t cols);

matrix_t *sum(const matrix_t *l, const matrix_t *r);
matrix_t *mul(const matrix_t *left, const matrix_t *right);

matrix_t *copy_matrix(matrix_t *source);

void free_matrix(matrix_t *matrix);

#endif  // INC_MATRIX_H_
