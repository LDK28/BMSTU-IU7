#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCORRECT_ALLOCATE_ERROR -1
#define INCORRECT_POINTER_ERROR -2
#define INCORRECT_INPUT_ERROR -3

long**allocate_matrix(size_t n, size_t m);
long reallocate_matrix(long ***data, size_t *lines, size_t *columns, long dif_lines, long dif_columns);
long input_matrix(long **data, size_t n, size_t m);
long output_matrix(long **data, size_t n, size_t m);
void free_matrix(long **data, size_t n);

#endif
