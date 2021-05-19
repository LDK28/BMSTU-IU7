#include"matrix.h"
#include"figure.h"
#include"rc.h"

void delete_matrix(matrix_t matrix, size_t n)
{
    if (!matrix)
        return;

    for (size_t i = 0; i < n; i++)
    {
        delete [] matrix[i];
        matrix[i] = NULL;
    }
    delete [] matrix;
    matrix = NULL;
}

rc_type allocate_zero_matrix(matrix_t& matrix, size_t n)
{
    if (!n)
        return ERR_MEMORY;
    matrix_t new_matrix = new bool*[n];
    if (!new_matrix)
        return ERR_MEMORY;

    rc_type rc = OK;

    size_t i;
    for (i = 0; i < n && !rc; i++)
    {
        new_matrix[i] = new bool[n];
        if (!new_matrix[i])
        {
            rc = ERR_MEMORY;
        }
    }
    if (rc)
    {
        delete_matrix(new_matrix, i);
        return rc;
    }

    matrix = new_matrix;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            matrix[i][j] = false;
        }
    }
    return OK;
}


