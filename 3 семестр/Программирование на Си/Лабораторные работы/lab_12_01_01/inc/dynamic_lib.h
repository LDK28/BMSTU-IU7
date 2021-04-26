#ifndef DYNAMIC_LIB
#define DYNAMIC_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCORRECT_INPUT_ERROR -1
#define OPEN_FILE_ERROR -2
#define INCORRECT_DATA_ERROR -3
#define INCORRECT_DYNAMICS_ERROR -4
#define OPEN_LIBRARY_ERROR -5

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

ARR_DLL long ARR_DECL count(const char *file_name);
ARR_DLL void ARR_DECL input_array(int *data, int *data_end, const char *file_name);
ARR_DLL int ARR_DECL compare(const void *x1, const void *x2);
ARR_DLL void ARR_DECL mysort(void *first, size_t number, size_t size, int(*comparator)(const void*, const void*));
ARR_DLL long ARR_DECL output_array(int *pa, int *pb, const char *file_name);
ARR_DLL int ARR_DECL key(const int *pa_src, const int *pb_src, int *pa_dst, size_t max_size, size_t *cur_size);

#endif
