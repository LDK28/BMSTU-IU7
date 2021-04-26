#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#define __USE_MINGW_ANSI_STDIO 1

#define INCORECT_COMMAND_ERROR -1
#define INCORRECT_FILE_NAME_ERROR -2
#define INCORRECT_DATA_ERROR -3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long average(FILE *f, double *num);
#endif