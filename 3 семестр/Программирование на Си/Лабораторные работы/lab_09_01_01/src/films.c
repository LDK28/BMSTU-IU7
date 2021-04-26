#include "films.h"

int check_field(char *field)
{
    if (!strcmp("title", field))
        return TITLE;
    if (!strcmp("name", field))
        return NAME; 
    if (!strcmp("year", field))
        return YEAR;
    return EMPTY;
}

int compare_films(film_t a, film_t b, int field)
{
    if (field == YEAR)
        return a.year - b.year;
    else if (field == NAME)
        return strcmp(a.name, b.name);
    else
        return strcmp(a.title, b.title);
}

void init_film(film_t *pfilm, char *title, char *name, long year)
{
    pfilm->title = title;
    pfilm->name = name;
    pfilm->year = year;
}

char*get_line(FILE *file)
{
    if (!file)
        return NULL;

    char *string;
    int ch;
    size_t len = 0;

    while ((ch = fgetc(file)) != '\n' && ch != EOF)
        ++len;
    if (len == 0)
        return NULL;
    fseek(file, -(len + 1), SEEK_CUR);

    string = malloc((len + 1) * sizeof(char));
    if (!(string))
        return NULL;
    size_t i;
    for (i = 0; (ch = fgetc(file)) != '\n' && ch != EOF; ++i)
        *(string + i) = ch;
    *(string + i) = 0;

    return string;
}

int read_film(FILE *file, film_t *pfilm)
{
    if (!file)
        return INCORRECT_POINTER_ERROR;
    
    char *title;
    char *name;
    long year;
    int ch;

    title = get_line(file);
    if (!title)
        return INCORRECT_DATA_ERROR;
    name = get_line(file);
    if (!name)
    {
        free(title);
        return INCORRECT_DATA_ERROR;
    }
    if (fscanf(file, "%ld", &year) != 1)
    {
        free(title);
        free(name);
        return INCORRECT_DATA_ERROR;
    }

    if (year < 0)
    {
        free(title);
        free(name);
        return INCORRECT_DATA_ERROR;
    }
    
    while ((ch = fgetc(file)) != '\n' && ch != EOF);

    init_film(pfilm, title, name, year);
    return EXIT_SUCCESS;
}

size_t count_films(FILE *file)
{
    if (!file)
        return 0;
    film_t buf;
    size_t count = 0;

    while ((read_film(file, &buf)) == EXIT_SUCCESS)
    {
        free(buf.name);
        free(buf.title);
        ++count;
    }
    
    if (count == 0)
        return 0;
    
    return count;
}

void read_films_array(FILE *file, film_t *pfilm, size_t count)
{
    fseek(file, 0, SEEK_SET);

    for (size_t i = 0; i < count; ++i)
        (read_film(file, (pfilm + i)));
}

size_t binary_search(film_t *films, const size_t count, const char *key, long field)
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

        while ((j > 0) && compare_films(*(films + j - 1), cur_film, field) > 0)
        {
            *(films + j) = *(films + j - 1);
            --j;
        }
        *(films + j) = cur_film;
    }
}

void free_films(film_t *films, size_t count)
{
    if (films)
    {
        for (size_t i = 0; i < count; ++i)
        {
            free((films + i)->name);
            free((films + i)->title);
        }
        free(films);
    }
}

film_t *allocate_films(size_t count)
{
    film_t *films = calloc(count, sizeof(film_t));
    if (!films)
        return NULL;
    for (size_t i = 0; i < count; ++i)
    {
        (films + i)->name = NULL;
        (films + i)->title = NULL;
        (films + i)->year = 0;
    }
    return films;
}

void output_films(film_t *films, size_t count)
{
    for (size_t i = 0; i < count; ++i)
        printf("%s\n%s\n%ld\n", (films + i)->title, (films + i)->name, (films + i)->year);
}
