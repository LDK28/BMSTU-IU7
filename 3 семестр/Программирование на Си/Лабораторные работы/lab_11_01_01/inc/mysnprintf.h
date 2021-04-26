#ifndef MYSNPRINTF_H
#define MYSNPRINTF_H

#define INCORRECT_ARGS_ERROR -1
#define INCORRECT_FORMAT_ERROR -2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int my_snprintf(char *restrict buffer, size_t buf_size, const char *restrict format, ...);

#endif
