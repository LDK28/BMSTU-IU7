#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>

#include "arr_queue.h"
#include "list_queue.h"

typedef enum { QUEUE_LIST, QUEUE_ARRAY } queue_type_t;

typedef struct {
  queue_type_t type;
  union {
    queue_list_t *list;
    queue_array_t *array;
  } queue;
} queue_t;

queue_t *create_queue(queue_type_t type);

void free_queue(queue_t *queue);

void empty_queue(queue_t *queue);

bool is_empty_queue(const queue_t *queue);

bool push_queue(queue_t *queue, const qtype_t *item);
bool pop_queue(queue_t *queue, qtype_t *item);

void get_queue(const queue_t *queue, qtype_t *item);

size_t length_queue(const queue_t *queue);
size_t get_queue_memory_size(const size_t size, queue_type_t type);

#endif
