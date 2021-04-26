#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#define __USE_MINGW_ANSI_STDIO 1
#define NMAX 258
#define WMAX 17
#define LONG_STRING_ERROR -1
#define LONG_WORD_ERROR -2
#define EMPTY_STRING_ERROR -3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long input(char *string);
long make_words(const char *string, char words[][WMAX], size_t *array_len);

#endif 