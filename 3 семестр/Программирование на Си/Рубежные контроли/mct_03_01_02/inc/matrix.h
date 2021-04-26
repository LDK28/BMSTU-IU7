#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

long**allocate_matrix(size_t n, size_t m);
long reallocate_matrix(long ***data, size_t *lines, size_t *columns, size_t dif_lines, size_t dif_columns);
long input_matrix(long **data, size_t n, size_t m);
long output_matrix(long **data, size_t n, size_t m);
void free_matrix(long **data, size_t n);

#endif
