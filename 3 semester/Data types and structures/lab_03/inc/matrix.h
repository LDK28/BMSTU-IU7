#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <time.h>

#define MATRIX_TYPE_SPECIF "lg"
typedef double matrix_type_t;

typedef struct matrix {
  size_t rows;
  size_t cols;
  matrix_type_t **data;
} matrix_t;

typedef struct sparse_matrix {
  size_t rows;
  size_t cols;
  size_t count;
  matrix_type_t *elements;
  size_t *elements_rows;
  size_t *cols_starts;
} sparse_matrix_t;

matrix_t *init_matrix(size_t rows, size_t cols);
void free_matrix(matrix_t *matrix);
sparse_matrix_t *init_sparse_matrix(size_t rows, size_t cols, size_t count);
void free_sparse_matrix(sparse_matrix_t *matrix);
sparse_matrix_t *matrix_to_sparse(matrix_t *matrix);
matrix_t *sparse_to_matrix(sparse_matrix_t *sparse);

matrix_t *mul(const matrix_t *left, const matrix_t *right, clock_t *time);

sparse_matrix_t *mul_sparse(const sparse_matrix_t *left,
                            const sparse_matrix_t *right, clock_t *time);

#endif  // MATRIX_H_