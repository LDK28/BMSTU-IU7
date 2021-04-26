#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 64

size_t input(long a[], size_t n)
{
	size_t i;
	for (i = 0; i < n; ++i)
		if (scanf("%ld", a + i) != 1)
			return i;
	return i;
}

void output(long a[], size_t n)
{
	for (size_t i = 0; i < n; ++i)
		printf("%ld ", *(a + i));
}

long sum(long a[], size_t n)
{
	long sum = 0;
	for (size_t i = 0; i < n; ++i)
		sum += abs(*(a + i));
	return sum;
}

int main(void)
{
	size_t n;
	size_t p;
	long a[NMAX];

	if ((scanf("%zu", &n) != 1) && (n > NMAX))
		return EXIT_FAILURE;
	if ((scanf("%zu", &p) != 1) && (p > n))
		return EXIT_FAILURE;
	if (input(a, n) != n)
		return EXIT_FAILURE;

	long f = sum(a, p);
	for (size_t i = p - 1; i < n; ++i)
	{
		if (*(a + i) > f)
		{
			for (size_t j = n - 1; j >= i; --j)
				*(a + j) = *(a + j + 1);
			--i;
			--n;
		}
	}

	output(a, n);
}