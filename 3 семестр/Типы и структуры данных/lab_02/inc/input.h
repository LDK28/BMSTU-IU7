#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>

void input_number(char *message, int *number, int beg, int end);
void input_bool(char *message, int *number);
void input_string(char *message, char *string, int max_len);

#endif

