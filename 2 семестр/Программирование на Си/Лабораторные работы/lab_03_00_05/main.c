#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#define NMAX 10

long input(long a[][NMAX], size_t n, size_t m)
{
	size_t i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < m; ++j)
			if (scanf("%ld", *(a + i) + j) != 1)
				return 1;
	return 0;
}

long func(long a[][NMAX], size_t n, size_t m)
{
	long arr[100];
	size_t len = 0;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
		{
			long divider = 1, k = 0;
			while (divider <= *(*(a + i) + j))
			{
				if (*(*(a + i) + j) % divider == 0)
					++k;
				++divider;
				if (k > 2)
					break;
			}
			if (k == 2)
			{
				*(arr + len) = *(*(a + i) + j);
				++len;
			}
		}
	if (len == 0)
		return 1;

	for (size_t i = 0; i < (len / 2); ++i)
	{
		long tmp = *(arr + i);
		*(arr + i) = *(arr + len - 1 - i);
		*(arr + len - 1 - i) = tmp;
	}
	
	len = 0;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
		{
			long divider = 1, k = 0;
			while (divider <= *(*(a + i) + j))
			{
				if (*(*(a + i) + j) % divider == 0)
					++k;
				++divider;
				if (k > 2)
					break;
			}
			if (k == 2)
			{
				*(*(a + i) + j) = *(arr + len);
				++len;
			}
		}
	return 0;
}

void output(long a[][NMAX], size_t n, size_t m)
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
	long a[NMAX][NMAX];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;
	if ((scanf("%zu", &m) != 1) || (m > NMAX) || (m < 1))
		return EXIT_FAILURE;

	if (input(a, n, m) != 0)
		return EXIT_FAILURE;
	
	if (func(a, n, m) != 0)
		return EXIT_FAILURE;
	
	output(a, n, m);
	return EXIT_SUCCESS;
}