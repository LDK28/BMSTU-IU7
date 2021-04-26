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

void output(long a[], size_t n)
{
	for (size_t i = 0; i < n; ++i)
		printf("%ld\n", *(a + i));
}

long new_array(long a[], size_t n, long new[], size_t len)
{
	for (size_t i = 0; i < n; ++i)
	{
		long last_num = abs(*(a + i)) % 10;
		long first_num = abs(*(a + i));
		while (first_num > 9)
		{
			first_num /= 10;
		}
		if (first_num == last_num)
		{
			*(new + len) = *(a + i);
			len += 1;
		}
	}
	return len;
}

int main(void)
{
	size_t n;
	long a[NMAX];

	if ((scanf("%zu", &n) != 1) || (n > NMAX) || (n < 1))
		return EXIT_FAILURE;

	if (input(a, n) != n)
		return EXIT_FAILURE;

	long new[NMAX];
	size_t len = 0;
	
	len = new_array(a, n, new, len);
	if (len == 0)
		return EXIT_FAILURE;
	
	output(new, len);

	return EXIT_SUCCESS;
}
