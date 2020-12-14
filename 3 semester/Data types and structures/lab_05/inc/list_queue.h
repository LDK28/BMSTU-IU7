#ifndef _LIST_QUEUE_H_
#define _LIST_QUEUE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "request.h"

typedef request_t qtype_t; 

typedef struct node node_t;
struct node {
    qtype_t data;
    node_t *next;
};

typedef struct {
    node_t *head, *tail;
    size_t length;
} queue_list_t;


queue_list_t *create_queue_list();
void free_queue_list(queue_list_t *queue);
void empty_queue_list(queue_list_t *queue);

bool is_empty_queue_list(const queue_list_t *queue);

bool push_queue_list(queue_list_t *queue, const qtype_t *item);
bool pop_queue_list(queue_list_t *queue, qtype_t *item);

void get_queue_list(const queue_list_t *queue, qtype_t *item);

size_t length_queue_list(const queue_list_t *queue);
size_t get_queue_list_memory_size(const size_t capacity);


#endif // _LIST_QUEUE_H_
