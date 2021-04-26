#include "films.h"

long scan(const char *file_name, film_t *films, size_t *i)
{
    FILE *f;
    f = fopen(file_name, "r");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    char string[NMAX];
    while (fgets(string, NMAX + 1, f))
    {
        if (!strrchr(string, '\n') || (strlen(string) < 2))
            return INCORRECT_DATA_ERROR;
        *strrchr(string, '\n') = '\0';
        strncpy((films + *i)->title, string, NMAX);
        if (!fgets(string, NMAX + 1, f))
            return INCORRECT_DATA_ERROR;
        if (!strrchr(string, '\n') || (strlen(string) < 2))
            return INCORRECT_DATA_ERROR;
        *strrchr(string, '\n') = '\0';
        strncpy((films + *i)->name, string, NMAX);
        if (fscanf(f, "%ld", &(films + *i)->year) != 1)
            return INCORRECT_DATA_ERROR;
        if ((films + *i)->year <= 0)
            return INCORRECT_DATA_ERROR;
        char ch = fgetc(f);
        if (ch != '\n' && ch != EOF)
            return INCORRECT_DATA_ERROR;
        ++*i;
        if (*i == SMAX && !feof(f))
            return INCORRECT_DATA_ERROR;
    }
    if (*i == 0)
        return INCORRECT_DATA_ERROR;
    fclose(f);
    return EXIT_SUCCESS;
}

size_t bnrsrch(film_t *films, const size_t count, const char *key, long field)
{
    size_t mid;
    long low = 0;
    long high = count - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (field == TITLE)
        {
            if (strcmp(key, (films + mid)->title) > 0)
                low = mid + 1;
            else if (strcmp(key, (films + mid)->title) < 0)
                high = mid - 1;
            else
                return mid;
        }
        else if (field == NAME)
        {
            if (strcmp(key, (films + mid)->name) > 0)
                low = mid + 1;
            else if (strcmp(key, (films + mid)->name) < 0)
                high = mid - 1;
            else
                return mid;
        }
        else if (field == YEAR)
        {
            long key_y = atoi(key);
            if (key_y > (films + mid)->year)
                low = mid + 1;
            else if (key_y < (films + mid)->year)
                high = mid - 1;
            else
                return mid;
        }
    }
    return count;
}

void sort(film_t *films, const size_t count, long field)
{
    for (size_t i = 0; i < count; ++i)
    {
        film_t cur_film;
        cur_film = *(films + i);
        size_t j = i;
        if (field == TITLE)
            while (strcmp((films + j - 1)->title, cur_film.title) > 0 && (j > 0))
            {
                *(films + j) = *(films + j - 1);
                --j;
            }
        else if (field == NAME)
            while (strcmp((films + j - 1)->name, cur_film.name) > 0 && (j > 0))
            {
                *(films + j) = *(films + j - 1);
                --j;
            }
        else if (field == YEAR)
            while (((films + j - 1)->year > cur_film.year) && (j > 0))
            {
                *(films + j) = *(films + j - 1);
                --j;
            }
        *(films + j) = cur_film;
    }
}

long title(const char *file_name, const char *key)
{
    film_t films[15];
    size_t count = 0;
    if (scan(file_name, films, &count))
        return EXIT_FAILURE;
    sort(films, count, TITLE);
    if (*key != '\0')
    {
        size_t mid = bnrsrch(films, count, key, TITLE);
        if (mid == count)
            printf("Not found");
        else
            printf("%s\n%s\n%ld\n", (films + mid)->title, (films + mid)->name, (films + mid)->year);
    }
    else
        for (size_t i = 0; i < count; ++i)
            printf("%s\n%s\n%ld\n", (films + i)->title, (films + i)->name, (films + i)->year);
    return EXIT_SUCCESS;    
}

long name(const char *file_name, const char *key)
{
    film_t films[15];
    size_t count = 0;
    if (scan(file_name, films, &count))
        return EXIT_FAILURE;
    sort(films, count, NAME);
    
    if (*key != '\0')
    {
        size_t mid = bnrsrch(films, count, key, NAME);
        if (mid == count)
            printf("Not found");
        else
            printf("%s\n%s\n%ld\n", (films + mid)->title, (films + mid)->name, (films + mid)->year);
    }  
    else
        for (size_t i = 0; i < count; ++i)
            printf("%s\n%s\n%ld\n", (films + i)->title, (films + i)->name, (films + i)->year);
    return EXIT_SUCCESS;
}

long year(const char *file_name, const char *key)
{
    film_t films[15];
    size_t count = 0;
    if (scan(file_name, films, &count))
        return EXIT_FAILURE;
    sort(films, count, YEAR);
    
    if (*key != '\0')
    {
        if (atoi(key) <= 0)
            return INCORRECT_COMMAND_ERROR;
        size_t mid = bnrsrch(films, count, key, YEAR);
        if (mid == count)
            printf("Not found");
        else
            printf("%s\n%s\n%ld\n", (films + mid)->title, (films + mid)->name, (films + mid)->year);
    }  
    else
        for (size_t i = 0; i < count; ++i)
            printf("%s\n%s\n%ld\n", (films + i)->title, (films + i)->name, (films + i)->year);
    return EXIT_SUCCESS;
}