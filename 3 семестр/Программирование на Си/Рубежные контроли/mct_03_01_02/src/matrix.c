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

long reallocate_matrix(long ***data, size_t *lines, size_t *columns, size_t dif_lines, size_t dif_columns)
{
    if (!(*data))
        return EXIT_FAILURE;
    
    if (dif_columns)
    {
        *columns += dif_columns;

        size_t i;
        for (i = 0; i < *lines; ++i)
        {
            long *tmp_i = NULL;
            tmp_i = realloc(*(*data + i), (*columns) * sizeof(long));
            if (!tmp_i)
            {
                free_matrix(*data, *lines);
                return EXIT_FAILURE;
            }
            else 
                *(*data + i) = tmp_i;
        }
    }

    if (dif_lines)
    {
        if (dif_lines < 0)
        {
            for (size_t i = *lines + dif_lines; i < *lines; ++i)
                free(*(data + i));
        }

        *lines += dif_lines;
        long **tmp = realloc(*data, (*lines) * sizeof(long *));
        if (!tmp)
        {
            free_matrix(*data, *lines);
            return EXIT_FAILURE;
        }
        else
            *data = tmp;

        for (size_t i = *lines; i < *lines; ++i)
        {
            *(*data + i) = malloc((*columns) * sizeof(long));
            if (!(*(*data + i)))
            {
                free_matrix(*data, (*lines) - i);
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

long input_matrix(long **data, size_t n, size_t m)
{
    if (!data)
        return EXIT_FAILURE;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (scanf("%ld", *(data + i) + j) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

long output_matrix(long **data, size_t lines, size_t columns)
{
    if (!data)
        return EXIT_FAILURE;
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
