#include "random_matrix.h"

#include <stdio.h>
#include <string.h>

#include "io_matrix.h"
#include "matrix.h"

static void swap(void *first, void *second, void *dop_memory, size_t size) {
  memcpy(dop_memory, first, size);
  memcpy(first, second, size);
  memcpy(second, dop_memory, size);
}

matrix_t *create_random_matrix(size_t rows, size_t cols, size_t elements) {
  matrix_t *matrix = init_matrix(rows, cols);

  for (size_t k = 0; k < elements; k++)
    matrix->data[k / cols][k % cols] =
        rand() % (MAX_VALUE - MIN_VALUE) + MIN_VALUE;

  char temp[sizeof(matrix_type_t)];

  for (size_t i = rows * cols - 1; i > 0; i--) {
    size_t j = rand() % (i + 1);
    swap(&(matrix->data[i / cols][i % cols]),
         &(matrix->data[j / cols][j % cols]), temp, sizeof(matrix_type_t));
  }

  return matrix;
}

matrix_t *create_random_matrix_by_occupancy(size_t rows, size_t cols,
                                            size_t occupancy) {
  return create_random_matrix(rows, cols, rows * cols * occupancy / 100);
}
