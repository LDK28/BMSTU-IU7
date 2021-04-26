#ifndef LIST_STACK_H
#define LIST_STACK_H

#include "utility.h"

typedef struct node {
    struct node* next;
    double value;
} node_t;

typedef struct list_stack {
    node_t *list;
    node_t *free_nodes;
} list_stack_t;

list_stack_t* init_list_stack();
node_t* create_node();
int push_list_stack(list_stack_t *stack);
int pop_list_stack(list_stack_t *stack, double *element);
void free_list_stack(list_stack_t *stack);
int print_list_stack(list_stack_t *list_stack);

#endif
