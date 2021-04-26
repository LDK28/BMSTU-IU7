#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#define NMAX 10

long input(long a[][NMAX + 10], size_t n, size_t m)
{
	size_t i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (scanf("%ld", *(a + i) + j) != 1)
				return 1;
	return 0;
}

size_t func(long a[][NMAX + 10], size_t n, size_t m)
{
	for (size_t i = 0; i < n; ++i)
	{
		long count = 0;
		for (size_t j = 0; j < m; ++j)
		{
			long sum = 0, tmp = abs(*(*(a + i) + j));
			while (tmp > 0)
			{
				sum += tmp % 10;
				tmp /= 10;
			}
			if (sum % 2 == 1)
				count += 1;
		}
		if (count > 1)
		{
			for (size_t k = n; k > i; --k)
				for (size_t z = 0; z < m; ++z)
					*(*(a + k) + z) = *(*(a + k - 1) + z);
			for (size_t p = 0; p < m; ++p)
				*(*(a + i) + p) = -1;
			++n;
			++i;
		}
	}
	return n;
}

void output(long a[][NMAX + 10], size_t n, size_t m)
{
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
			printf("%ld ", *(*(a + i) + j));
		printf("\n");
	}
}

int main(void)
{
	size_t n, m;
	long a[NMAX + 10][NMAX + 10];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;
	if ((scanf("%zu", &m) != 1) || (m > NMAX) || (m < 1))
		return EXIT_FAILURE;

	if (input(a, n, m) != 0)
		return EXIT_FAILURE;
	
	n = func(a, n, m);
	output(a, n, m);

	return EXIT_SUCCESS;
}
