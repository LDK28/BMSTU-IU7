#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inc/io.h"
char *filename_data_global = NULL;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Укажитe имя файла с данными в параметрах запуска программы\n");
        return -1;
    }

    filename_data_global = argv[1];

    srand(time(NULL));

    system("clear");

    print_menu();
    return 0;
}
