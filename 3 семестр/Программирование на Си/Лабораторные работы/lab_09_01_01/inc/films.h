#ifndef FILMS_H
#define FILMS_H

#define __USE_MINGW_ANSI_STDIO 1

#define INCORRECT_ARGS_ERROR -1
#define OPEN_FILE_ERROR -2
#define INCORRECT_DATA_ERROR -3
#define INCORRECT_POINTER_ERROR -4
#define INCORRECT_ALLOCATE_ERROR -5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum field
{
    TITLE,
    NAME,
    YEAR,
    EMPTY,
};

struct film
{
    char *title;
    char *name;
    long year;
};

typedef struct film film_t;

int check_field(char *field);
size_t count_films(FILE *file);
void read_films_array(FILE *file, film_t *pfilm, size_t count);
size_t binary_search(film_t *films, const size_t count, const char *key, long field);
void sort(film_t *films, const size_t count, long field);
film_t *allocate_films(size_t count);
void free_films(film_t *films, size_t count);
void output_films(film_t *films, size_t count);

#endif
