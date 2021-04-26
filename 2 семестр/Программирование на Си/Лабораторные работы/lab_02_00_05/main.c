#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#define NMAX 10

long input(long *pa, const long *pe)
{
	while (pa < pe)
	{
		if (scanf("%ld", pa) != 1)
			return pe - pa;
		++pa;
	}
	return pe - pa;
}

long maximum(long *pa, long *pe)
{
	long max = 0;
	--pe;
	while (pa <= pe)
	{
		if (*pa + *pe > max)
			max = *pa + *pe;
		++pa;
		--pe;
	}
	return max;
}

int main(void)
{
	size_t n;
	long a[NMAX], *pa, *pe;

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;
	
	pa = a;
	pe = a + n;

	if (input(pa, pe) != 0)
		return EXIT_FAILURE;
	
	long max = maximum(pa, pe);
	
	printf("%ld", max);
}
