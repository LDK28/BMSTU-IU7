#include "films.h"

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return INCORRECT_COMMAND_ERROR;
    if (!strcmp(*(argv + 2), "title"))
    {
        if (argc == 4)
            if (title(*(argv + 1), *(argv + 3)))
                return EXIT_FAILURE;
        if (argc == 3)
            if (title(*(argv + 1), "\0"))
                return EXIT_FAILURE;
    }
    else if (!strcmp(*(argv + 2), "name"))
    {
        if (argc == 4)
            if (name(*(argv + 1), *(argv + 3)))
                return EXIT_FAILURE;
        if (argc == 3)
            if (name(*(argv + 1), "\0"))
                return EXIT_FAILURE;
    }
    else if (!strcmp(*(argv + 2), "year"))
    {
        if (argc == 4)
            if (year(*(argv + 1), *(argv + 3)))
                return EXIT_FAILURE;
        if (argc == 3)
            if (year(*(argv + 1), "\0"))
                return EXIT_FAILURE;
    }
    else
        return INCORRECT_COMMAND_ERROR;
    return EXIT_SUCCESS;
}