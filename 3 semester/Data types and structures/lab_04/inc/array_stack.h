#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include "utility.h"

#define ARRAY_CAPACITY 10

#define INCORRECT_INPUT_ERROR -1
#define FULL_STACK_ERROR -2

typedef struct array_stack {

    double array[ARRAY_CAPACITY];

    double *ptr_start;
    double *ptr_end;

    double *cur_ptr_start;
    double *cur_ptr_end;

} array_stack_t;

void init_array(array_stack_t *array);
void print_array_stack(array_stack_t array);
int add_array_item(array_stack_t *array);
int get_array_item(array_stack_t *array);

#endif
