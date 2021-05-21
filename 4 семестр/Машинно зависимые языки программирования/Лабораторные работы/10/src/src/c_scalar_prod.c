#include "c_scalar_prod.h"

void dot_prod_vector_arrays_c(double *res, const dvec *a, const dvec *b, int n)
{
    for (const dvec *a_end = a + n; a < a_end; ++a, ++b)
        *(res++) =
            (*a)[0] * (*b)[0] +
            (*a)[1] * (*b)[1] +
            (*a)[2] * (*b)[2] +
            (*a)[3] * (*b)[3];
}
