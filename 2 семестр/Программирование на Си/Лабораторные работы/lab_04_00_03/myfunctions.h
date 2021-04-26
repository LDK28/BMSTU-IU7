#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#define __USE_MINGW_ANSI_STDIO 1
#define NMAX 258
#define WMAX 17
#define EMPTY_STRING_ERROR -1
#define LONG_STRING_ERROR -2
#define LONG_WORD_ERROR -3
#define NOT_ENOUGH_WORDS_ERROR -4
#define SAME_WORDS_ERROR -5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long make_words(char *string, char words[][WMAX], size_t *array_len);
void del_letters(char words[][WMAX], size_t *array_len);

#endif 