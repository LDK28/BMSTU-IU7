#include "asm_scalar_prod.h"

void dot_prod_vector_arrays_asm(double *res, const dvec *a, const dvec *b, int n)
{
    for (const dvec *a_end = a + n - 1; a < a_end; a += 2, b += 2)
    {
        asm(
            "vmovupd ymm0, %1\n"
            "vmovupd ymm1, %2\n"
            "vmovupd ymm2, %3\n"
            "vmovupd ymm3, %4\n"
            "vmulpd ymm0, ymm0, ymm1\n"
            "vmulpd ymm2, ymm2, ymm3\n"
            "vhaddpd ymm1, ymm0, ymm2\n"
            "vextractf128 xmm3, ymm1, 1\n"
            "vaddpd ymm0, ymm1, ymm3\n"
            "movupd xmmword ptr [%0], xmm0\n"
            :
            : "r"(res), "m"(*a), "m"(*b), "m"(*(a + 1)), "m"(*(b + 1))
            : "ymm0", "ymm1", "ymm2", "ymm3");
    }

    if (n & 1)
    {
        asm volatile(
            "vmovupd ymm0, %1\n"
            "vmovupd ymm1, %2\n"
            "vmovupd ymm2, %3\n"
            "vmovupd ymm3, %4\n"
            "vmulpd ymm0, ymm0, ymm1\n"
            "vmulpd ymm2, ymm2, ymm3\n"
            "vhaddpd ymm1, ymm0, ymm2\n"
            "vextractf128 xmm3, ymm1, 1\n"
            "vaddpd ymm0, ymm1, ymm3\n"
            "movlpd %0, xmm0\n"
            :
            : "m"(*res), "m"(*a), "m"(*b), "m"(*a), "m"(*b)
            : "ymm0", "ymm1", "ymm2", "ymm3", "memory");
    }
}
