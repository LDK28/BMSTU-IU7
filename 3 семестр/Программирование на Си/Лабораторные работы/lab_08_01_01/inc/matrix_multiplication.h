#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define INCORRECT_POINTER_ERROR -2

long**matrix_multiplication(long **matrix1, size_t lines1, size_t columns1, long **matrix2, size_t lines2, size_t columns2);
long copy_matrix(long **matrix1, long **matrix2, size_t lines, size_t columns);
long make_one_matrix(long **matrix, size_t size);

#endif
