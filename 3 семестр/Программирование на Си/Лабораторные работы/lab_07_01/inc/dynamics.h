#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCORRECT_INPUT_ERROR -1
#define OPEN_FILE_ERROR -2
#define INCORRECT_DATA_ERROR -3
#define INCORRECT_DYNAMICS_ERROR -4

long count(const char *file_name);
int*allocate_array(size_t size);
void input_array(int *data, int *data_end, const char *file_name);
int compare(const void *x1, const void *x2);
void mysort(void *first, size_t number, size_t size, int(*comparator)(const void*, const void*));
long output_array(int *pa, int *pb, const char *file_name);
int key(const int *pa_src, const int *pb_src, int **pa_dst, int **pb_dst);


#endif
