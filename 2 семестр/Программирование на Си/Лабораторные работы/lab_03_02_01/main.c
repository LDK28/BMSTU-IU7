#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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

void func(long a[][NMAX], size_t n, size_t m, long mas[])
{
	for (size_t j = 0; j < m; ++j)
	{
		long k = 1;
		if (n == 1)
			k = 0;
		else
			for (size_t i = 0; i < n - 1; ++i)
				if (((*(*(a + i) + j) >= 0) && ((*(*(a + i + 1) + j)) >= 0)) || ((*(*(a + i) + j) <= 0) && ((*(*(a + i + 1) + j)) <= 0)))
				{
					k = 0;
					break;
				}
		*(mas + j) = k;
	}
}

void output(long mas[], size_t m)
{
	for (size_t i = 0; i < m; ++i)
	{
		printf("%ld ", *(mas + i));
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
	
	long mas[NMAX];
	func(a, n, m, mas);
	output(mas, m);
	
	return EXIT_SUCCESS;
}
