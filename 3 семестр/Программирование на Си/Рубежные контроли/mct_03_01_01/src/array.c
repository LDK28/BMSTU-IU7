#include "array.h"

size_t set_len(double **arr, size_t len, size_t newlen)
{
    if (!len)
    {
        if (newlen)
            *arr = malloc(newlen * sizeof(double));
    }
    else if (!newlen)
        free(*arr);
    else if (len != newlen)
    {
        double *tmp = realloc(*arr, newlen * sizeof(double));
        if(!tmp)
        {
            free(*arr);
            return EXIT_FAILURE;
        }
        else
            *arr = tmp;
    }
    return newlen;
}

long input_array_mean(double *data, size_t n, double *mean)
{
    double sum = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (scanf("%lf", data + i) != 1)
            return EXIT_FAILURE;
        sum += *(data + i);
    }
    *mean = sum / n;
    return EXIT_SUCCESS;
}

void output_array(double *data, size_t n)
{ 
    for (size_t i = 0; i < n; ++i)
        printf("%lf ", *(data + i));
}

long insert_mean(double **data, size_t *n, double mean)
{
    if (!(*data))
        return EXIT_FAILURE;

    size_t dif = 0;

    for (size_t i = 0; i < *n; ++i)
        if (*(*data + i) < mean)
            ++dif;

    if (!dif)
        return EXIT_SUCCESS;
    
    *n = set_len(data, *n, *n + dif);
    if (*n < 0)
        return EXIT_FAILURE;

    for (size_t i = 0; i < *n; ++i)
        if (*(*data + i) < mean)
        {
            for (size_t j = *n - dif; j > i; --j)
                *(*data + j) = *(*data + j - 1);
            --dif;
            *(*data + i + 1) = mean;
        }
    return EXIT_SUCCESS;
}
