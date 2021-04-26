#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NMAX 10

size_t input(long a[], size_t n)
{
	size_t i;
	for (i = 0; i < n; ++i)
		if (scanf("%ld", a + i) != 1)
			return i;
	return i;
}

double arithmetic_mean(long a[], size_t n)
{
	double mean;
	long sum = 0, count = 0;
	for (size_t i = 0; i < n; ++i)
		if (*(a + i) < 0)
		{
			sum += *(a + i);
			count += 1;
		}
	if (sum == 0)
		mean = 0.0;
	else
		mean = (double)sum / (double)count;
	return mean;
}

int main(void)
{
	size_t n;
	long a[NMAX];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;

	if (input(a, n) != n)
		return EXIT_FAILURE;
	
	double mean = arithmetic_mean(a, n);
	if (fabs(mean) < 1e-8)
		return EXIT_FAILURE;
	else
	{
		printf("%.6lf", mean);
		return EXIT_SUCCESS;
	}
}
