#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

size_t set_len(double **arr, size_t len, size_t newlen);
long input_array_mean(double *data, size_t n, double *mean);
void output_array(double *data, size_t n);
long insert_mean(double **data, size_t *n, double mean);

#endif
