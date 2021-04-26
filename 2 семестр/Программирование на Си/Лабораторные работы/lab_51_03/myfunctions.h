#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#define __USE_MINGW_ANSI_STDIO 1

#define INCORRECT_COMMAND_ERROR -1
#define OPEN_FILE_ERROR -2
#define INCORRECT_DATA_ERROR -3
#define INCORRECT_POSITION_ERROR -4
#define DETERMINE_FILE_SIZE_ERROR -5
#define INCORRECT_FILE_ERROR -6;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long file_size(FILE *f, size_t *size);
long create_bin_file(const char *file_name);
long print_bin_file(const char *file_name);
long get_number_by_pos(const char *file_name, size_t pos, int *num);
long put_number_by_pos(const char *file_name, size_t pos, int num);
long sort_bin_file(const char *file_name);

#endif