#include "myfunctions.h"

int main(void)
{
    FILE *f = stdin;
    long num1, num2;
	
    if (func(f, &num1, &num2))
        return EXIT_FAILURE;
    else
    {
        printf("%ld %ld", num2, num1);
        return EXIT_SUCCESS;
    }
}