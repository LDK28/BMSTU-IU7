#include "myfunctions.h"

int main(int argc, char **argv)
{
    FILE *f;

    if (argc != 2)
        return INCORECT_COMMAND_ERROR;

    f = fopen(*(argv + 1), "r");
    if (f == NULL)
        return INCORRECT_FILE_NAME_ERROR;

    double num;
    if (average(f, &num) != 0)
        return INCORRECT_DATA_ERROR;
    printf("%.5lf", num);

    fclose(f);
    return EXIT_SUCCESS;
}