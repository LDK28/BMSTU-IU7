#define __USE_MINGW_ANSI_STDIO 1

#include "matrix.h"
#include "matrix_change.h"
#include "matrix_multiplication.h"

int main(void)
{
    setbuf(stdout, NULL);
    size_t n, m;
    long tmp_inp;
    if (scanf("%ld", &tmp_inp) != 1 || tmp_inp <= 0)
        return INCORRECT_INPUT_ERROR;
    n = tmp_inp;
    if (scanf("%ld", &tmp_inp) != 1 || tmp_inp <= 0)
        return INCORRECT_INPUT_ERROR;
    m = tmp_inp;

    long **data1 = NULL;
    data1 = allocate_matrix(n, m);
    if (!data1)
        return INCORRECT_ALLOCATE_ERROR;
    if (input_matrix(data1, n, m))
    {
        free_matrix(data1, n);
        return INCORRECT_INPUT_ERROR;
    }

    size_t p, q;
    if (scanf("%ld", &tmp_inp) != 1 || tmp_inp <= 0)
    {
        free_matrix(data1, n);
        return INCORRECT_INPUT_ERROR;
    }
    p = tmp_inp;
    if (scanf("%ld", &tmp_inp) != 1 || tmp_inp <= 0)
    {
        free_matrix(data1, n);
        return INCORRECT_INPUT_ERROR;
    }
    q = tmp_inp;

    long **data2 = NULL;
    data2 = allocate_matrix(p, q);
    if (!data2)
    {
        free_matrix(data1, n);
        return INCORRECT_ALLOCATE_ERROR;
    }
    if (input_matrix(data2, p, q))
    {
        free_matrix(data1, n);
        free_matrix(data2, p);
        return INCORRECT_INPUT_ERROR;
    }

    if (make_square_matrix(&data1, &n, &m))
    {
        free_matrix(data2, p);
        return EXIT_FAILURE;
    }
    if (make_square_matrix(&data2, &p, &q))
    {
        free_matrix(data1, n);
        return EXIT_FAILURE;
    }

    while (n < p)
    {
        if (add_elements(&data1, &n, &m))
        {
            free_matrix(data2, p);
            return INCORRECT_ALLOCATE_ERROR;
        }
    }
    while (n > p)
    {        
        if (add_elements(&data2, &p, &q))
        {
            free_matrix(data1, n);
            return INCORRECT_ALLOCATE_ERROR;
        }
    }

    size_t pow1, pow2;
    if (scanf("%zu %zu", &pow1, &pow2) != 2)
    {
        free_matrix(data1, n);
        free_matrix(data2, p);
        return INCORRECT_INPUT_ERROR;
    }

    long **multiplication = NULL;
    if (pow1 >= 2)
    {
        multiplication = matrix_multiplication(data1, n, m, data1, n, m);
        pow1 -= 2;
    }
    else
    {
        multiplication = allocate_matrix(n, n);
        if (pow1 == 0)
        {
            if (make_one_matrix(multiplication, n))
            {
                free_matrix(data1, n);
                free_matrix(data2, p);
                return INCORRECT_POINTER_ERROR;
            }
        }
        else if (pow1 == 1)
        {
            if (copy_matrix(multiplication, data1, n, m))
            {
                free_matrix(data1, n);
                free_matrix(data2, p);
                return INCORRECT_POINTER_ERROR;
            }
            --pow1;
        }         
    }
    while (pow1)
    {
        long **tmp = NULL;
        tmp = matrix_multiplication(multiplication, n, m, data1, n, m);
        free_matrix(multiplication, n);
        if (!tmp)
        {
            free_matrix(data1, n);
            free_matrix(data2, p);
            return EXIT_FAILURE;
        }
        else
            multiplication = tmp;
        --pow1;
    }
    
    if (pow2 == 0)
    {
        if (make_one_matrix(data2, p))
        {
            free_matrix(data1, n);
            free_matrix(data2, p);
            free_matrix(multiplication, n);
            return INCORRECT_POINTER_ERROR;
        }
    }
    while (pow2)
    {
        long **tmp = NULL;
        tmp = matrix_multiplication(multiplication, n, m, data2, p, q);
        free_matrix(multiplication, n);
        if (!tmp)
        {
            free_matrix(data1, n);
            free_matrix(data2, p);
            return EXIT_FAILURE;
        }
        else
            multiplication = tmp;
        --pow2;
    }
    
    if (output_matrix(multiplication, n, n))
    {
        free_matrix(data1, n);
        free_matrix(data2, p);
        free_matrix(multiplication, n);
        return EXIT_FAILURE;
    }


    free_matrix(data1, n);
    free_matrix(data2, p);
    free_matrix(multiplication, n);

    return EXIT_SUCCESS;
}
