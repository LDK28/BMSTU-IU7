#include "matrix_change.h"

typedef struct max_elem
{
    long element;
    size_t position;
} max_elem_t;

void sort(max_elem_t *pa, size_t len)
{
    max_elem_t new_element;
    long location;
 
    for (size_t i = 1; i < len; i++)
    {
        new_element = *(pa + i);
        location = i - 1;
        while (location >= 0 && (pa + location)->position > new_element.position)
        {
            *(pa + location + 1) = *(pa + location);
            location = location - 1;
        }
        *(pa + location + 1) = new_element;
    }
}

size_t min_element(max_elem_t *pa, size_t len)
{
    long min = pa->element;
    size_t min_pos = 0;
    for (size_t i = 1; i < len; ++i)
        if ((pa + i)->element < min)
        {
            min = (pa + i)->element;
            min_pos = i;
        }

    return min_pos;
}

void deletion_columns(long ***data, size_t *lines, size_t *columns)
{
    long max_len = *columns - *lines;
    max_elem_t *pa = malloc(max_len * sizeof(max_elem_t));
    long len = 0;
    long cur_max;

    for (size_t j = 0; j < *columns; ++j)
    {
        cur_max = *(**data + j);
        for (size_t i = 1; i < *lines; ++i)
            if (*(*(*data + i) + j) > cur_max)
                cur_max = *(*(*data + i) + j);

        if (len == max_len)
        {
            size_t min_pos = min_element(pa, len);
            if (cur_max > (pa + min_pos)->element)
            {
                (pa + min_pos)->element = cur_max;
                (pa + min_pos)->position = j;
            }
        }
        else
        {
            (pa + len)->element = cur_max;
            (pa + len)->position = j;
            ++len;
        }
    }

    sort(pa, len);

    for (long k = len - 1; k >= 0; --k)
        if ((pa + k)->position < *columns - 1)
            for (size_t i = 0; i < *lines; ++i)
                for (size_t j = (pa + k)->position; j < *columns - 1; ++j)
                    *(*(*data + i) + j) = *(*(*data + i) + j + 1);

    reallocate_matrix(data, lines, columns, 0, -max_len);
    free(pa);
}

void deletion_lines(long ***data, size_t *lines, size_t *columns)
{
    long max_len = *lines - *columns;
    max_elem_t *pa = malloc(max_len * sizeof(max_elem_t));
    long len = 0;
    long cur_max;

    for (size_t i = 0; i < *lines; ++i)
    {
        cur_max = **(*data + i);
        for (size_t j = 1; j < *columns; ++j)
            if (*(*(*data + i) + j) > cur_max)
                cur_max = *(*(*data + i) + j);

        if (len == max_len)
        {
            size_t min_pos = min_element(pa, len);
            if (cur_max > (pa + min_pos)->element)
            {
                (pa + min_pos)->element = cur_max;
                (pa + min_pos)->position = i;
            }
        }
        else
        {
            (pa + len)->element = cur_max;
            (pa + len)->position = i;
            ++len;
        }
    }

    sort(pa, len);

    for (long k = len - 1; k >= 0; --k)
        if ((pa + k)->position < *lines - 1)
            for (size_t i = (pa + k)->position; i < *lines - 1; ++i)
                for (size_t j = 0; j < *columns; ++j)
                    *(*(*data + i) + j) = *(*(*data + i + 1) + j);
    
    reallocate_matrix(data, lines, columns, -max_len, 0);
    free(pa);
}

long make_square_matrix(long ***data, size_t *lines, size_t *columns)
{
    if (!(*data))
        return INCORRECT_POINTER_ERROR;
    if (*columns > *lines)
        deletion_columns(data, lines, columns);
    else if (*columns < *lines)
        deletion_lines(data, lines, columns);
    if (!(*data))
        return INCORRECT_ALLOCATE_ERROR;
    return EXIT_SUCCESS;    
}

long add_elements(long ***data, size_t *lines, size_t *columns)
{
    if (!(*data))
        return INCORRECT_POINTER_ERROR;
    reallocate_matrix(data, lines, columns, 1, 1);
    if (!(*data))
        return INCORRECT_ALLOCATE_ERROR;

    for (size_t j = 0; j < *columns - 1; ++j)
    {
        double sum = 0;
        size_t i;
        for (i = 0; i < *lines - 1; ++i)
            sum += *(*(*data + i) + j);
        *(*(*data + i) + j) = floor(sum / i);
    }
    for (size_t i = 0; i < *lines; ++i)
    {
        long max = **(*data + i);
        size_t j;
        for (j = 1; j < *columns - 1; ++j)
            if (*(*(*data + i) + j) > max)
                max = *(*(*data + i) + j);
        *(*(*data + i) + j) = max;
    }
        
    return EXIT_SUCCESS;
}
