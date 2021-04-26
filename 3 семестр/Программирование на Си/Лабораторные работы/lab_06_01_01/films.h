#ifndef FILMS_H
#define FILMS_H

#define __USE_MINGW_ANSI_STDIO 1
#define NMAX 26
#define SMAX 15

#define INCORRECT_COMMAND_ERROR -1
#define OPEN_FILE_ERROR -2
#define INCORRECT_DATA_ERROR -3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum field
{
    TITLE,
    NAME,
    YEAR,
};
struct film
{
    char title[NMAX];
    char name[NMAX];
    long year;
};

typedef struct film film_t;
long scan(const char *file_name, film_t *films, size_t *count);
long title(const char *file_name, const char *key);
long name(const char *file_name, const char *key);
long year(const char *file_name, const char *key);

#endif