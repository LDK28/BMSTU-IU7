#include "matrix.h"

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

void free_matrix(matrix_t *matrix) {
  if (!matrix) return;
  // for (size_t i = 0; i < matrix->rows; i++) free(matrix->data[i]);
  free(matrix->data);
  free(matrix);
}

sparse_matrix_t *init_sparse_matrix(size_t rows, size_t cols, size_t count) {
  sparse_matrix_t *matrix = malloc(sizeof(sparse_matrix_t));

  matrix->cols = cols;
  matrix->rows = rows;
  matrix->count = count;

  matrix->elements = calloc(sizeof(matrix_type_t), count);
  matrix->elements_rows = calloc(sizeof(size_t), count);
  matrix->cols_starts = calloc(sizeof(size_t), cols + 1);

  matrix->cols_starts[cols] = count;

  return matrix;
}

void free_sparse_matrix(sparse_matrix_t *matrix) {
  if (!matrix) return;

  free(matrix->elements);
  free(matrix->elements_rows);
  free(matrix->cols_starts);

  free(matrix);
}

sparse_matrix_t *matrix_to_sparse(matrix_t *matrix) {
  size_t count = 0;
  for (size_t i = 0; i < matrix->rows; i++)
    for (size_t j = 0; j < matrix->cols; j++)
      if (matrix->data[i][j]) count++;

  sparse_matrix_t *sparse =
      init_sparse_matrix(matrix->rows, matrix->cols, count);

  count = 0;
  for (size_t j = 0; j < matrix->cols; j++) {
    sparse->cols_starts[j] = count;
    for (size_t i = 0; i < matrix->rows; i++) {
      if (matrix->data[i][j]) {
        sparse->elements[count] = matrix->data[i][j];
        sparse->elements_rows[count] = i;
        count++;
      }
    }
  }

  return sparse;
}

matrix_t *sparse_to_matrix(sparse_matrix_t *sparse) {
  matrix_t *matrix = init_matrix(sparse->rows, sparse->cols);

  for (size_t j = 0; j < sparse->cols; j++)
    for (size_t i = sparse->cols_starts[j]; i < sparse->cols_starts[j + 1]; i++)
      matrix->data[sparse->elements_rows[i]][j] = sparse->elements[i];

  return matrix;
}

matrix_t *mul(const matrix_t *left, const matrix_t *right, clock_t *time) {
  if (!left || !right) return NULL;
  if (left->cols != right->rows) return NULL;

  matrix_t *new_matrix = init_matrix(left->rows, right->cols);

  if (new_matrix == NULL) return NULL;

  clock_t start = clock();

  for (size_t i = 0; i < left->rows; i++)
    for (size_t k = 0; k < right->rows; k++)
      for (size_t j = 0; j < right->cols; j++)
        new_matrix->data[i][j] += left->data[i][k] * right->data[k][j];

  *time = clock() - start;

  return new_matrix;
}

sparse_matrix_t *mul_sparse(const sparse_matrix_t *left,
                            const sparse_matrix_t *right, clock_t *time) {
  if (!left || !right) return NULL;
  if (left->cols != right->rows) return NULL;
  if (left->rows != 1) return NULL;

  matrix_type_t vec[right->cols];
  for (size_t i = 0; i < right->cols; i++) vec[i] = 0;

  clock_t start = clock();

  for (size_t j = 0; j < right->cols; j++)
    for (size_t i = right->cols_starts[j]; i < right->cols_starts[j + 1]; i++) {
      size_t k = right->elements_rows[i];
      size_t el_pos = left->cols_starts[k];
      if (left->cols_starts[k + 1] - el_pos != 1) continue;
      vec[j] += right->elements[i] * left->elements[el_pos];
    }

  size_t count = 0;
  for (size_t i = 0; i < right->cols; i++)
    if (vec[i]) count++;

  *time = clock() - start;

  sparse_matrix_t *new_matrix = init_sparse_matrix(1, right->cols, count);

  start = clock();

  count = 0;
  for (size_t j = 0; j < right->cols; j++) {
    new_matrix->cols_starts[j] = count;
    if (vec[j]) {
      new_matrix->elements[count] = vec[j];
      new_matrix->elements_rows[count] = 0;
      count++;
    }
  }

  *time += clock() - start;

  return new_matrix;
}
