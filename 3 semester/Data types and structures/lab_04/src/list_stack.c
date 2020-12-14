#include "list_stack.h"

#include <stdlib.h>

list_stack_t* init_list_stack()
{
    list_stack_t* stack = calloc(sizeof(list_stack_t), 1);
    return stack;
}

node_t* create_node(double value)
{
    node_t* node = calloc(sizeof(node_t), 1);
    node->value = value;

    return node;
}

int push_list_stack(list_stack_t *stack) {

    printf("Enter a number: ");
    double tmp;
    if (scanf("%lf", &tmp) != 1)
    {
        puts("Invalid input.");
        return EXIT_FAILURE;
    }

    node_t *node = stack->free_nodes;

    if (node)
        stack->free_nodes = stack->free_nodes->next;
    else
        node = create_node(tmp);

    node->next = stack->list;
    stack->list = node;

    return 0;
}

int pop_list_stack(list_stack_t *stack, double *element)
{
    if (!stack->list)
    {
        puts("\nThe stack is empty.");
        return EXIT_FAILURE;
    }

    node_t* node = stack->list;

    *element = node->value;

    stack->list = node->next;

    // free(node);
    node->next = stack->free_nodes;
    stack->free_nodes = node;

    return 0;
}

void free_list_stack(list_stack_t* stack) {
  if (!stack) return;
  node_t* cur;

  cur = stack->list;
  while (cur) {
    node_t* l = cur;
    cur = cur->next;
    free(l);
  }

  cur = stack->free_nodes;
  while (cur) {
    node_t* l = cur;
    cur = cur->next;
    free(l);
  }

  free(stack);
}

int print_list_stack(list_stack_t *list_stack)
{
    size_t size = 0;
    size_t free_size = 0;

    node_t *cur = list_stack->list;
    while (cur)
    {
        size++;
        cur = cur->next;
    }

    cur = list_stack->free_nodes;
    while (cur)
    {
        free_size++;
        cur = cur->next;
    }

    printf("\nStack has %zu element(s)\n", size);

    printf("List of free memory areas has %zu element(s)\n\n", free_size);

    if (size)
        printf("Elements of the stack:\n");
    for (node_t *cur = list_stack->list; cur; cur = cur->next)
        printf("Address: %p   Element: %10lf\n", cur, cur->value);

    if (free_size)
        printf("\nAddresses of the free area:\n");
    for (node_t *cur = list_stack->free_nodes; cur; cur = cur->next)
        printf("Address: %p \n", cur);

    return 0;
}
