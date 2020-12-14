#ifndef IO_MATRIX_H
#define IO_MATRIX_H

#include <stdio.h>

#include "matrix.h"

matrix_t *read_matrix(FILE *file);
void print_matrix(FILE *file, matrix_t *matrix);
void print_sparse_matrix(FILE *file, matrix_t *matrix);

matrix_t *create_matrix_from_coord(FILE *stream);
matrix_t *create_matrix_full(FILE *file);

#endif  // IO_MATRIX_H