

#include <stdlib.h>

#include "arr_queue.h"
#include "list_queue.h"

typedef enum { QUEUE_LIST, QUEUE_ARRAY } queue_type_t;

typedef struct queue {
  queue_type_t type;
  union {
    queue_list_t *list;
    queue_array_t *array;
  } queue;
} queue_t;

queue_t *create_queue(queue_type_t type) {
  queue_t *queue = calloc(sizeof(*queue), 1);
  queue->type = type;
  switch (type) {
    case QUEUE_LIST:
      queue->queue.list = create_queue_list();
      break;
    case QUEUE_ARRAY:
      queue->queue.array = create_queue_array();
      break;
  }

  return queue;
}

void free_queue(queue_t *queue) {
  if (!queue) return;
  switch (queue->type) {
    case QUEUE_LIST:
      free_queue_list(queue->queue.list);
      break;
    case QUEUE_ARRAY:
      free_queue_array(queue->queue.array);
      break;
  }
  free(queue);
}

void empty_queue(queue_t *queue) {
  switch (queue->type) {
    case QUEUE_LIST:
      empty_queue_list(queue->queue.list);
      break;
    case QUEUE_ARRAY:
      empty_queue_array(queue->queue.array);
      break;
  }
}

bool is_empty_queue(const queue_t *queue) {
  switch (queue->type) {
    case QUEUE_LIST:
      return is_empty_queue_list(queue->queue.list);
    case QUEUE_ARRAY:
      return is_empty_queue_array(queue->queue.array);
  }

  return 1;
}

bool push_queue(queue_t *queue, const qtype_t *item) {
  switch (queue->type) {
    case QUEUE_LIST:
      return push_queue_list(queue->queue.list, item);
    case QUEUE_ARRAY:
      return push_queue_array(queue->queue.array, item);
  }
  return 1;
}
bool pop_queue(queue_t *queue, qtype_t *item) {
  switch (queue->type) {
    case QUEUE_LIST:
      return pop_queue_list(queue->queue.list, item);
    case QUEUE_ARRAY:
      return pop_queue_array(queue->queue.array, item);
  }
  return 1;
}

void get_queue(const queue_t *queue, qtype_t *item) {
  switch (queue->type) {
    case QUEUE_LIST:
      return get_queue_list(queue->queue.list, item);
    case QUEUE_ARRAY:
      return get_queue_array(queue->queue.array, item);
  }
}


size_t length_queue(const queue_t *queue)
{
   switch (queue->type) {
    case QUEUE_LIST:
      return length_queue_list(queue->queue.list);
    case QUEUE_ARRAY:
      return length_queue_array(queue->queue.array);
  }
  return 0;
}

size_t get_queue_memory_size(const size_t size, queue_type_t type) {
  switch (type) {
    case QUEUE_LIST:
      return get_queue_list_memory_size(size);
    case QUEUE_ARRAY:
      return get_queue_array_memory_size(size);
  }

  return 0;
}