#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#define NMAX 10

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

size_t deletion(long a[], size_t n)
{
	for (size_t i = 0; i < n;)
	{
		long k = 1;
		while ((k * k != *(a + i)) && (k <= *(a + i) / 2))
			k += 1;
		if (k * k == *(a + i))
		{
			n -= 1;
			for (size_t j = i; j < n; ++j)
				*(a + j) = *(a + j + 1);
		}
		else
			++i;
	}
	return n;
}

int main(void)
{
	size_t n;
	long a[NMAX];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;

	if (input(a, n) != n)
		return EXIT_FAILURE;

	size_t new_len = deletion(a, n);
	if (new_len == 0)
		return EXIT_FAILURE;
	
	output(a, new_len);

	return EXIT_SUCCESS;
}
