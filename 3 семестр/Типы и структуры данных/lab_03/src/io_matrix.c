#include "io_matrix.h"

#include <stdio.h>

#include "matrix.h"

matrix_t *create_matrix_full(FILE *file) {
  if (!file) return NULL;
  size_t rows = 0, cols = 0;

  if (fscanf(file, "%zu%zu", &rows, &cols) != 2) return NULL;

  matrix_t *matrix = init_matrix(rows, cols);

  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      if (fscanf(file, "%" MATRIX_TYPE_SPECIF, &(matrix->data[i][j])) != 1) {
        free_matrix(matrix);
        return NULL;
      }

  return matrix;
}

matrix_t *create_matrix_from_coord(FILE *stream) {
  int err = 0;

  size_t cols = 0;
  size_t rows = 0;
  size_t count = 0;
  if (stream == stdin)
    printf("Enter number of lines, colums and non-zero elements: ");

  if (!err) err = fscanf(stream, "%zu%zu%zu", &rows, &cols, &count) != 3;

  if (!err && rows * cols < count) err = 1;

  matrix_t *matrix = NULL;
  if (!err) matrix = init_matrix(rows, cols);

  if (!err && !matrix) err = 1;

  for (size_t k = 0; k < count && !err; k++) {
    size_t i = 0, j = 0;
    double element = 0;
    if (stream == stdin)
      printf("%3zu) Enter line, column and element: ", k + 1);
    err = fscanf(stream, "%zu%zu%" MATRIX_TYPE_SPECIF, &i, &j, &element) != 3;
    if (!err && (i == 0 || j == 0)) err = 1;
    if (!err && (i > rows || j > cols)) err = 1;
    if (!err) matrix->data[i - 1][j - 1] = element;
  }

  if (err && matrix) {
    free_matrix(matrix);
    matrix = NULL;
  }

  return matrix;
}

void print_matrix(FILE *file, matrix_t *matrix) {
  if (file == stdout) printf("Matrix sizes: ");

  fprintf(file, "%zu %zu\n", matrix->rows, matrix->cols);

  for (size_t i = 0; i < matrix->rows; i++) {
    for (size_t j = 0; j < matrix->cols; j++)
      fprintf(file, "%7" MATRIX_TYPE_SPECIF " ", matrix->data[i][j]);
    fprintf(file, "\n");
  }
}

void print_sparse_matrix(FILE *file, matrix_t *matrix)
{
  sparse_matrix_t *tmp = matrix_to_sparse(matrix);
  fprintf(file, "\n\nA:  ");
  for (size_t i = 0; i < tmp->count; i++)
    fprintf(file, "%5" MATRIX_TYPE_SPECIF " ", tmp->elements[i]);

  fprintf(file, "\nIA: ");
  for (size_t i = 0; i < tmp->count; i++)
    fprintf(file, "%5zu ", tmp->elements_rows[i]);

  fprintf(file, "\nj:  ");
  int check_row;
  for (size_t j = 0; j < matrix->cols; ++j)
  {
    check_row = 0;
    for (size_t i = 0; i < matrix->rows; ++i)
      if (check_row == 0 && matrix->data[i][j])
      {
        check_row = 1;
        fprintf(file, "%5zu ", j);
        break;
      }
  }

  fprintf(file, "\nNk: ");
  size_t count = 0;
  check_row = 0;
  for (size_t j = 0; j < matrix->cols; ++j)
  {
    check_row = 0;
    for (size_t i = 0; i < matrix->rows; ++i)
      if (matrix->data[i][j])
      {
        if (check_row == 0)
        {
          check_row = 1;
          fprintf(file, "%5zu ", count);
        }
        ++count;
      }
  }

  fprintf(file, "\n");
  free_sparse_matrix(tmp);
}

void print_empty_matrix(FILE *file, size_t rows, size_t cols) {
  fprintf(file, "%zu %zu\n", rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++)
      fprintf(file, "%" MATRIX_TYPE_SPECIF "\t", 0.);
    fprintf(file, "\n");
  }
}