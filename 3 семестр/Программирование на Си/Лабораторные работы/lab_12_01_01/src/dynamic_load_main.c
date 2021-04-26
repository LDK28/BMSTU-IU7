#include "../inc/dynamic_lib.h"
#include <windows.h>

typedef long(ARR_DECL *fn_count_t)(const char *file_name);
typedef void(ARR_DECL *fn_input_array_t)(int *data, int *data_end, const char *file_name);
typedef int(ARR_DECL *fn_compare_t)(const void *x1, const void *x2);
typedef void(ARR_DECL *fn_mysort_t)(void *first, size_t number, size_t size, int(*comparator)(const void*, const void*));
typedef long(ARR_DECL *fn_output_array_t)(int *pa, int *pb, const char *file_name);
typedef int(ARR_DECL *fn_key_t)(const int *pa_src, const int *pb_src, int *pa_dst, size_t max_size, size_t *cur_size);

int *allocate_array(size_t size)
{
    int *data = malloc(size * sizeof(int));
    if (!data)
        return data;
    for (size_t i = 0; i < size; ++i)
    {
        *(data + i) = 0;
    }
    return data;
}

int main(int argc, char **argv)
{
    HMODULE hlib;
    fn_count_t count;
    fn_input_array_t input_array;
    fn_compare_t compare;
    fn_mysort_t mysort;
    fn_output_array_t output_array;
    fn_key_t key;

    hlib = LoadLibrary("dynamiclib.dll");
    if (!hlib)
        return OPEN_LIBRARY_ERROR;
    
    count = (fn_count_t)GetProcAddress(hlib, "count");
    if (!count)
    {
        FreeLibrary(hlib);
        return OPEN_LIBRARY_ERROR;
    }

    input_array = (fn_input_array_t)GetProcAddress(hlib, "input_array");
    if (!input_array)
    {
        FreeLibrary(hlib);
        return OPEN_LIBRARY_ERROR;
    }

    compare = (fn_compare_t)GetProcAddress(hlib, "compare");
    if (!compare)
    {
        FreeLibrary(hlib);
        return OPEN_LIBRARY_ERROR;
    }

    mysort = (fn_mysort_t)GetProcAddress(hlib, "mysort");
    if (!mysort)
    {
        FreeLibrary(hlib);
        return OPEN_LIBRARY_ERROR;
    }

    output_array = (fn_output_array_t)GetProcAddress(hlib, "output_array");
    if (!output_array)
    {
        FreeLibrary(hlib);
        return OPEN_LIBRARY_ERROR;
    }

    key = (fn_key_t)GetProcAddress(hlib, "key");
    if (!key)
    {
        FreeLibrary(hlib);
        return OPEN_LIBRARY_ERROR;
    }

    setbuf(stdout, NULL);
    if (argc > 4 || argc < 3)
    {
        FreeLibrary(hlib);
        return INCORRECT_INPUT_ERROR;
    }

    long size = count(*(argv + 1));
    if (size <= 0)
    {
        FreeLibrary(hlib);
        return EXIT_FAILURE;
    }
    
    int *pa = allocate_array(size);
    if (pa == NULL)
    {
        FreeLibrary(hlib);
        return INCORRECT_DYNAMICS_ERROR;
    }
    int *pb = pa + size;

    input_array(pa, pb, *(argv + 1));

    int *pa_dst = NULL, *pb_dst = NULL;
    size_t cur_size = 0;
    if (argc == 4)
    {
        if (!strcmp(*(argv + 3), "f"))
        {
            pa_dst = malloc((pb - pa) * sizeof(int));
            if (key(pa, pb, pa_dst, pb - pa, &cur_size))
            {
                free(pa);
                FreeLibrary(hlib);
                return EXIT_FAILURE;
            }
            else
            {
                free(pa);
                pb_dst = pa_dst + cur_size;
            }
        }
        else
        {
            free(pa);
            FreeLibrary(hlib);
            return INCORRECT_INPUT_ERROR;
        }
    }
    else
    {
        pa_dst = pa;
        pb_dst = pb;
    }

    mysort(pa_dst, pb_dst - pa_dst, sizeof(int), compare);

    if (output_array(pa_dst, pb_dst, *(argv + 2)))
    {
        free(pa_dst);
        FreeLibrary(hlib);
        return EXIT_FAILURE;
    }
    free(pa_dst);
    FreeLibrary(hlib);
    return EXIT_SUCCESS;
}
