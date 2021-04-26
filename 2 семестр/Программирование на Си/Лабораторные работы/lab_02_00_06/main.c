#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>
#include<sys/time.h>
#define NMAX 100000

size_t input(long a[], size_t n)
{
	size_t i;
	for (i = 0; i < n; ++i)
		if (scanf("%ld", a + i) != 1)
			return i;
	return i;
}

long process_1(long a[], size_t n)
{
	long max = 0;
	size_t i = 0, j = n - 1;
	while (i <= j)
	{
		if (a[i] + a[j] > max)
			max = a[i] + a[j];
		++i;
		--j;
	}
	return max;
}

long process_2(long a[], size_t n)
{
	long max = 0;
	size_t i = 0, j = n - 1;
	while (i <= j)
	{
		if (*(a + i) + *(a + j) > max)
			max = *(a + i) + *(a + j);
		++i;
		--j;
	}
	return max;
}

long process_3(long *pa, long *pe)
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
	long a[NMAX];
	
	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
	{
		return EXIT_FAILURE;
	}
	
	if (input(a, n) != n)
	{
		return EXIT_FAILURE;
	}
	
	long max;
	long *pa, *pe;
	
	pa = a;
	pe = a + n;
	
	struct timeval tv_start, tv_stop;
	int64_t elapsed_time;
	
	long sum1 = 0, sum2 = 0, sum3 = 0, n_iter = 10000;
	for (long i = 0; i < n_iter; ++i)
	{
		// 1-st func
		gettimeofday(&tv_start, NULL);
		max = process_1(a, n);
		gettimeofday(&tv_stop, NULL);
		elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
		(tv_stop.tv_usec - tv_start.tv_usec);
		sum1 += elapsed_time;

		// 2-nd func
		gettimeofday(&tv_start, NULL);
		max = process_2(a, n);
		gettimeofday(&tv_stop, NULL);
		elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
		(tv_stop.tv_usec - tv_start.tv_usec);
		sum2 += elapsed_time;
		
		// 3-nd func
		gettimeofday(&tv_start, NULL);
		max = process_3(pa, pe);
		gettimeofday(&tv_stop, NULL);
		elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
		(tv_stop.tv_usec - tv_start.tv_usec);
		sum3 += elapsed_time;
	}
	printf("Repeats: %ld\nSize of array: %zu\nTime of process_1/a[i](microseconds): %ld\nTime of process_2/*(a + i)(microseconds): %ld\nTime of process_3/*pa,*pe(microseconds): %ld\n", n_iter, n, sum1/n_iter, sum2/n_iter, sum3/n_iter);
	printf("Max: %ld", max);
}
