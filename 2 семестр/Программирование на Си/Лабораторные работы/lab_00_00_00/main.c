#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    long a;
    long b;
    long buf;

    if (scanf("%ld", &a) != 1)
		return EXIT_FAILURE;
	if (scanf("%ld", &b) != 1)
	    return EXIT_FAILURE;
	
    buf = a;
    a = b;
    b = buf;

    printf("%ld %ld", a, b);

    return EXIT_SUCCESS;
}
