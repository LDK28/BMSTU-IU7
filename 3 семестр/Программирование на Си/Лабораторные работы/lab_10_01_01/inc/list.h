#ifndef LIST_H
#define LIST_H


#define INCORRECT_POINTER_ERROR -1
#define INCORRECT_ALLOCATE_ERROR -1


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

void*pop_front(node_t **head);
void*pop_back(node_t **head);
void append(node_t **head_a, node_t **head_b);
void list_free_all(node_t *head);

#endif
