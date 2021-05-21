#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "common.h"

#include "asm_scalar_prod.h"
#include "c_scalar_prod.h"

#define GET_RND ((double)rand() / (double)(RAND_MAX))

typedef void scalar_prod(double *, const dvec *, const dvec *, int);

void measure_func(scalar_prod *dot)
{
    dvec a[ARRAY_SIZE], b[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        a[i][0] = GET_RND;
        a[i][1] = GET_RND;
        a[i][2] = GET_RND;
        a[i][3] = GET_RND;

        b[i][0] = GET_RND;
        b[i][1] = GET_RND;
        b[i][2] = GET_RND;
        b[i][3] = GET_RND;
    }

    double res[ARRAY_SIZE];

    clock_t start = clock();

    for (int m = 0; m < MEASUREMENT_REPEATS; ++m)
        dot(res, a, b, ARRAY_SIZE);

    clock_t end = clock();

    printf("\t%.3g s\n", ((double)(end - start)) / CLOCKS_PER_SEC / MEASUREMENT_REPEATS);
}

int main(void)
{
    printf("asm:");
    measure_func(dot_prod_vector_arrays_asm);
    printf("c:");
    measure_func(dot_prod_vector_arrays_c);

    return EXIT_SUCCESS;
}
