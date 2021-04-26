#define __USE_MINGW_ANSI_STDIO 1

#include "matrix.h"

int main(void)
{
    size_t n, m;
    if (scanf("%zu %zu", &n, &m) != 2)
        return EXIT_FAILURE;

    long **data = NULL;
    data = allocate_matrix(n, m);
    if (!data)
        return EXIT_FAILURE;

    if (input_matrix(data, n, m))
    {
        free_matrix(data, n);
        return EXIT_FAILURE;
    }
    
    long min_sum = 0;
    size_t min_line = 0;
    for (size_t j = 0; j < m; ++j)
    {
        min_sum += *(*data + j);
    }
    

    for (size_t i = 1; i < n; ++i)
    {
        long cur_sum = 0;
        for (size_t j = 0; j < m; ++j)
            cur_sum += *(*(data + i) + j);
        if (cur_sum < min_sum)
        {
            min_sum = cur_sum;
            min_line = i;
        }
    }
    for (size_t i = min_line; i < n - 1; ++i)
        for (size_t j = 0; j < m; ++j)
            *(*(data + i) + j) = *(*(data + i + 1) + j);
    
    if (reallocate_matrix(&data, &n, &m, -1, 0))
        return EXIT_FAILURE;

    output_matrix(data, n, m);

    free_matrix(data, n);
    return EXIT_SUCCESS;
}
