#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	long n;
	
	if (scanf("%ld", &n) != 1 || (n <= 0))
		return EXIT_FAILURE;
	
	while (n != 1)
	{
		long i = 2;
		while (n % i != 0)
		{
			i += 1;
		}
		printf("%ld\n", i);
		n /= i;
	}
	return EXIT_SUCCESS;
}
