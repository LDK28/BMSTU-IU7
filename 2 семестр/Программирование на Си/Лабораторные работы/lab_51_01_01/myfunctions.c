#include "myfunctions.h"

long func(FILE *f, long *num1, long *num2)
{
    long num;
    size_t count = 0;
    if (fscanf(f, "%ld", &num) == 1)
    {
        *num1 = num;
        *num2 = num;
        ++count;
        while (fscanf(f, "%ld", &num) == 1)
        {
            if (num > *num1)
            {
                *num2 = *num1;
                *num1 = num;
            }
            else if (num > *num2)
                *num2 = num;
            ++count;
        }
    }
    else
        return INCORRECT_INPUT_ERROR;
    if (count == 1)
        return ONLY_NUMBER_ERROR;
    return EXIT_SUCCESS;
}