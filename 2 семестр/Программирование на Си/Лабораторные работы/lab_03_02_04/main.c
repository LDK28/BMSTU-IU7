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
	long nums[NMAX];
	size_t len = 0;
	for (size_t i = 1; i < n; ++i)
		for (size_t j = n - i; j < m; ++j)
			if (abs(*(*(a + i) + j)) % 10 == 5)
			{
				*(nums + len) = *(*(a + i) + j);
				++len;
			}
	if (len == 0)
		return 0;
	else
	{
		size_t id_max = 0;
		for (size_t i = 0; i < len; ++i)
			if (*(nums + i) > *(nums + id_max))
				id_max = i;
		return *(nums + id_max);	
	}
}

int main(void)
{
	size_t n, m;
	long a[NMAX][NMAX];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;
	if ((scanf("%zu", &m) != 1) || (m > NMAX) || (m < 1) || (n != m))
		return EXIT_FAILURE;

	if (input(a, n, m) != 0)
		return EXIT_FAILURE;
	
	long num = func(a, n, m);
	if (num == 0)
		return EXIT_FAILURE;
	else
	{
		printf("%ld", num);
		return EXIT_SUCCESS;
	}
}