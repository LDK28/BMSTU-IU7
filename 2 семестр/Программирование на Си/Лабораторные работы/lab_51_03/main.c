#include "myfunctions.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return INCORRECT_COMMAND_ERROR;
    if (!strcmp(*(argv + 1), "c"))
    {
        if (create_bin_file(*(argv + 2)) != 0)
            return EXIT_FAILURE;
    }
    else if (!strcmp(*(argv + 1), "p")) 
    {       
        if (print_bin_file(*(argv + 2)) != 0)
            return EXIT_FAILURE;
    }
    else if (!strcmp(*(argv + 1), "s"))
    {
        if (sort_bin_file(*(argv + 2)) != 0)
            return EXIT_FAILURE;
    }
    else
        return INCORRECT_COMMAND_ERROR;
    
    return EXIT_SUCCESS;
}