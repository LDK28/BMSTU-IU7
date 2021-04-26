#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#define __USE_MINGW_ANSI_STDIO 1
#define INCORRECT_INPUT_ERROR -1
#define ONLY_NUMBER_ERROR -2

#include <stdio.h>
#include <stdlib.h>

long func(FILE *f, long *num1, long *num2);

#endif