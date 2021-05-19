#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "rc.h"

typedef bool **matrix_t;

void delete_matrix(matrix_t matrix, size_t n);
rc_type allocate_zero_matrix(matrix_t& matrix, size_t n);


#endif
