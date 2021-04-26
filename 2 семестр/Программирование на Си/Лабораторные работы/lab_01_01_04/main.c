#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	long n;
	long entrance, floor;
	
	if ((scanf("%ld", &n) != 1) || (n <= 0))
		return EXIT_FAILURE;
	
	entrance = (n - 1) / 36 + 1;
	n = (n - 1) % 36;
	floor = n / 4 + 1;
	
	printf("%ld %ld", entrance, floor);
	
	return EXIT_SUCCESS;
}
