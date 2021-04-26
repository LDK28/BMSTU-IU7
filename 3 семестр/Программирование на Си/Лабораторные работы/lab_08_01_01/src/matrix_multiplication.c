#include "matrix_multiplication.h"

long **matrix_multiplication(long **matrix1, size_t lines1, size_t columns1, long **matrix2, size_t lines2, size_t columns2)
{
    if (!matrix1 || !matrix2)
        return NULL;
    if (columns1 != lines2)
        return NULL;

    long **multiplication = NULL;
    multiplication = allocate_matrix(lines1, columns2);
    if (!multiplication)
        return NULL;
    
    for (size_t i = 0; i < lines1; ++i)
        for (size_t j = 0; j < columns2; ++j)
        {
            *(*(multiplication + i) + j) = 0;
            for (size_t k = 0; k < columns1; ++k)
                *(*(multiplication + i) + j) += (*(*(matrix1 + i) + k)) * (*(*(matrix2 + k) + j));
        }

    return multiplication;
}

long copy_matrix(long **matrix1, long **matrix2, size_t lines, size_t columns)
{
    if (!matrix2)
        return INCORRECT_POINTER_ERROR;
    for (size_t i = 0; i < lines; ++i)
        for (size_t j = 0; j < columns; ++j)
            *(*(matrix1 + i) + j) = *(*(matrix2 + i) + j);
    return EXIT_SUCCESS;       
}

long make_one_matrix(long **matrix, size_t size)
{
    if (!matrix)
        return INCORRECT_POINTER_ERROR;
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            if (i == j)
                *(*(matrix + i) + j) = 1;
            else
                *(*(matrix + i) + j) = 0;
    return EXIT_SUCCESS;
}
