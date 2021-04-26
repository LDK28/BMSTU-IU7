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

void sort(long a[][NMAX], size_t n, size_t m)
{
	long arr[NMAX];
	for (size_t i = 0; i < n; ++i)
	{
		long prod = 1;
		for (size_t j = 0; j < m; ++j)
			prod *= *(*(a + i) + j);
		*(arr + i) = prod;
	}
	
	for (size_t i = 0; i < n; ++i)
	{
		size_t id_min = i;
		for (size_t j = i; j < n; ++j)
			if (*(arr + j) < *(arr + id_min))
				id_min = j;
		if (id_min != i)
		{
			long tmp_arr = *(arr + i);
			*(arr + i) = *(arr + id_min);
			*(arr + id_min) = tmp_arr;
			for (size_t j = 0; j < m; ++j)
			{
				long tmp_a = *(*(a + i) + j);
				*(*(a + i) + j) = *(*(a + id_min) + j);
				*(*(a + id_min) + j) = tmp_a;
			}
		}
	}
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
	
	sort(a, n, m);
	output(a, n, m);

	return EXIT_SUCCESS;
}
