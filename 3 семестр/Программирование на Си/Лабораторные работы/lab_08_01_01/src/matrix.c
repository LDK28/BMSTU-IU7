#include "matrix.h"

long **allocate_matrix(size_t n, size_t m)
{
    long **data = calloc(n, sizeof(long *));
    if (!data)
        return NULL;
    for (size_t i = 0; i < n; i++)
    {
        *(data + i) = malloc(m * sizeof(long));
        if (!(*(data + i)))
        {
            free_matrix(data, n);
            return NULL;
        }
    }
    return data;
}

long reallocate_matrix(long ***data, size_t *lines, size_t *columns, long dif_lines, long dif_columns)
{
    if (!(*data))
        return INCORRECT_POINTER_ERROR;
    
    if (dif_columns)
    {
        if ((long)*columns + dif_columns < 0)
        {
            free_matrix(*data, *lines);
            *data = NULL;
            return INCORRECT_ALLOCATE_ERROR;
        }
        *columns += dif_columns;

        size_t i;
        for (i = 0; i < *lines; ++i)
        {
            long *tmp_i = NULL;
            tmp_i = realloc(*(*data + i), (*columns) * sizeof(long));
            if (!tmp_i)
            {
                free_matrix(*data, *lines);
                return INCORRECT_ALLOCATE_ERROR;
            }
            else
                *(*data + i) = tmp_i;
        }
    }

    if (dif_lines)
    {
        if ((long)*lines + dif_lines < 0)
        {
            free_matrix(*data, *lines);
            *data = NULL;
            return INCORRECT_ALLOCATE_ERROR;
        }
        if (dif_lines < 0)
            for (size_t i = *lines + dif_lines; i < *lines; ++i)
                free(*(*data + i));
        *lines += dif_lines;
        long **tmp = realloc(*data, (*lines) * sizeof(long *));
        if (!tmp)
        {
            free_matrix(*data, *lines);
            return INCORRECT_ALLOCATE_ERROR;
        }
        else
            *data = tmp;
        if (dif_lines > 0)
            for (size_t i = *lines - dif_lines; i < *lines; ++i)
            {
                long *tmp_i = malloc((*columns) * sizeof(long));
                if (!tmp_i)
                {
                    free_matrix(*data, (*lines) - i);
                    return INCORRECT_ALLOCATE_ERROR;
                }
                else
                    *(*data + i) = tmp_i;
            }
    }
    return EXIT_SUCCESS;
}

long input_matrix(long **data, size_t n, size_t m)
{
    if (!data)
        return INCORRECT_POINTER_ERROR;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (scanf("%ld", *(data + i) + j) != 1)
                return INCORRECT_INPUT_ERROR;
    return EXIT_SUCCESS;
}

long output_matrix(long **data, size_t lines, size_t columns)
{
    if (!data)
        return INCORRECT_POINTER_ERROR;
    for (size_t i = 0; i < lines; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
            printf("%ld ", *(*(data + i) + j)); 
        puts("");
    }
    return EXIT_SUCCESS;
}

void free_matrix(long **data, size_t n)
{
    if (data)
    {
        for (size_t i = 0; i < n; ++i)
            free(*(data + i));
        free(data);
    }
}
