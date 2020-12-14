#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "array_stack.h"
#include "list_stack.h"

void print_space(void);
void print_menu(void);
void get_choice(int *choice, int start, int stop);
void get_enter(void);
void menu();
int compare_methods();

#endif
