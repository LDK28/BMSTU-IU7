#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#define NMAX 100000

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
		printf("%ld\n", *(a + i));
}

void sort_insertions(long a[], size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		long cur = *(a + i);
		size_t j = i;
		while ((j > 0) && (*(a + j - 1) > cur))
		{
			*(a + j) = *(a + j - 1);
			j -= 1;
		}
		*(a + j) = cur;
	}
}

int main(void)
{
	size_t n;
	long a[NMAX];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;

	if (input(a, n) != n)
		return EXIT_FAILURE;
	
	sort_insertions(a, n);
	
	output(a, n);

	return EXIT_SUCCESS;
}
