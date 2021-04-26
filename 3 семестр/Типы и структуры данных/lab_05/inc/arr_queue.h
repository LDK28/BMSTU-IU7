#ifndef _ARR_QUEUE_H_
#define _ARR_QUEUE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "request.h"

typedef request_t qtype_t;

typedef struct {
    qtype_t *buffer;
    size_t capacity;
    size_t length;
    size_t head, tail;
} queue_array_t;


queue_array_t *create_queue_array();
void empty_queue_array(queue_array_t *queue);
void free_queue_array(queue_array_t *queue);

bool is_full_queue_array(const queue_array_t *queue);
bool is_empty_queue_array(const queue_array_t *queue);

bool push_queue_array(queue_array_t *queue, const qtype_t *item);
bool pop_queue_array(queue_array_t *queue, qtype_t *item);

void get_queue_array(const queue_array_t *queue, qtype_t *item);
size_t length_queue_array(const queue_array_t *queue);
size_t get_queue_array_memory_size(const size_t capacity);


#endif // _ARR_QUEUE_H_
