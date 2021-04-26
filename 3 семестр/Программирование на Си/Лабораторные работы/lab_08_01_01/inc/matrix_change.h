#ifndef MATRIX_CHANGE_H
#define MATRIX_CHANGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

long make_square_matrix(long ***data, size_t *lines, size_t *columns);
long add_elements(long ***data, size_t *lines, size_t *columns);

#endif
