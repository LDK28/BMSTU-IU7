#ifndef RANDOM_MATRIX_H_
#define RANDOM_MATRIX_H_

#include "matrix.h"

#define MAX_VALUE 1000
#define MIN_VALUE -1000

matrix_t *create_random_matrix(size_t rows, size_t cols, size_t elements);

matrix_t *create_random_matrix_by_occupancy(size_t rows, size_t cols,
                                            size_t occupancy);

#endif  // RANDOM_MATRIX_H_
