#include "polinom.h"


int main(void)
{
    setbuf(stdin, NULL);
    int action;
    if (get_action(&action))
        return INCORRECT_ACTION_ERROR;

    polinom_t *polinom = NULL;
    if (get_polinom(&polinom))
        return INCORRECT_DATA_ERROR;

    if (action == VAL)
    {
        long number;
        long result;
        if (scanf("%ld", &number) != 1)
        {
            list_free_all(polinom);
            return INCORRECT_DATA_ERROR;
        }
        result = val(polinom, number);
        printf("%ld", result);
    }
    else if (action == DDX)
    {
        polinom_t *polinom_ddx = NULL;
        polinom_ddx = ddx(polinom);
        if (!polinom_ddx)
        {
            list_free_all(polinom);
            return INCORRECT_DATA_ERROR;
        }

        print_polinom(polinom_ddx);
        list_free_all(polinom_ddx);
    }
    else if (action == SUM)
    {
        polinom_t *polinom2 = NULL;
        polinom_t *result = NULL;
        if (get_polinom(&polinom2))
        {
            list_free_all(polinom);
            return INCORRECT_DATA_ERROR;
        }
        
        result = sum(polinom, polinom2);

        if (!result)
        {
            list_free_all(polinom);
            list_free_all(polinom2);
            return INCORRECT_DATA_ERROR;
        }
        print_polinom(result);

        list_free_all(result);
        list_free_all(polinom2);
    }
    else if (action == DVD)
    {
        polinom_t *even = NULL;
        polinom_t *odd = NULL;

        if (dvd(polinom, &even, &odd) != EXIT_SUCCESS)
        {
            list_free_all(polinom);
            return EXIT_FAILURE;
        }

        print_polinom(even);
        print_polinom(odd);

        list_free_all(even);
        list_free_all(odd);
    }    

    list_free_all(polinom);
    return EXIT_SUCCESS;
}
