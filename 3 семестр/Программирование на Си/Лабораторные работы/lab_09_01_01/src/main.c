#include "films.h"


int main(int argc, char **argv)
{
    if (argc == 3 || argc == 4)
    {
        int field = check_field(*(argv + 2));
        if (field == EMPTY)
            return INCORRECT_ARGS_ERROR;
        
        FILE *file;
        file = fopen(*(argv + 1), "r");
        if (!file)
            return OPEN_FILE_ERROR;
        
        size_t count = count_films(file);
        if (!count)
        {
            fclose(file);
            return INCORRECT_DATA_ERROR;
        }      

        film_t *films = NULL;
        films = allocate_films(count);

        read_films_array(file, films, count);
        fclose(file);

        sort(films, count, field);

        if (argc == 3)
            output_films(films, count);
        else
        {
            if (field == YEAR && strtol(*(argv + 3), NULL, 10) <= 0)
            {
                free_films(films, count);
                return INCORRECT_ARGS_ERROR;
            }
            size_t pos = binary_search(films, count, *(argv + 3), field);
            if (pos == count)
                printf("Not found");
            else
                printf("%s\n%s\n%ld\n", (films + pos)->title, (films + pos)->name, (films + pos)->year);
        }

        free_films(films, count);
    }
    else
        return INCORRECT_ARGS_ERROR;
    
    return EXIT_SUCCESS;
}



