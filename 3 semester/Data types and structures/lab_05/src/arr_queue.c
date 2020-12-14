#include "arr_queue.h"

#include <stdbool.h>
#include <stdlib.h>

int init_capacity = 8;

queue_array_t *create_queue_array() {
  queue_array_t *queue = malloc(sizeof(queue_array_t));

  queue->capacity = init_capacity;
  queue->buffer = calloc(init_capacity, sizeof(qtype_t));
  queue->head = queue->tail = 0;
  queue->length = 0;

  return queue;
}

void empty_queue_array(queue_array_t *queue) {
  queue->head = queue->tail = queue->length = 0;
}

/**
 * @brief Resize a queue array object
 *
 * @param queue
 * @param size
 * @return queue_array_t*
 */
queue_array_t *resize_queue_array(queue_array_t *queue, const size_t size) {
  queue->buffer = realloc(queue->buffer, sizeof(size * sizeof(qtype_t)));
  queue->capacity = size;
  queue->head = queue->tail = 0;
  queue->length = 0;

  return queue;
}
/**
 * @brief Free queue array object
 *
 * @param queue
 */
void free_queue_array(queue_array_t *queue) {
  free(queue->buffer);
  free(queue);
}
/**
 * @brief Check is full queue array
 *
 * @param queue
 * @return true
 * @return false
 */
bool is_full_queue_array(const queue_array_t *queue) {
  return queue->length == queue->capacity;
}
/**
 * @brief Check is empty queue array
 *
 * @param queue
 * @return true
 * @return false
 */
bool is_empty_queue_array(const queue_array_t *queue) {
  return !(queue->length);
}

/**
 * @brief Increase capaciry of queue array object
 * 
 * @param queue 
 */
void increase_queue_array(queue_array_t *queue)
{
  size_t new_capacity = queue->capacity * 2;
  
  qtype_t *buffer = malloc(new_capacity * sizeof(qtype_t));
  size_t length = length_queue_array(queue);
  qtype_t *end = buffer + length;
  
  while (!is_empty_queue_array(queue))
  {
    end--;
    pop_queue_array(queue, end);
  }

  free(queue->buffer);
  
  queue->buffer= buffer;
  queue->capacity = new_capacity;
  queue->head = 0;
  queue->length = queue->tail = length;
}

/**
 * @brief Push back element to the queue array
 *
 * @param queue
 * @param item
 * @return true
 * @return false
 */
bool push_queue_array(queue_array_t *queue, const qtype_t *item) {
  if (is_full_queue_array(queue)) {
    increase_queue_array(queue);
  }

  queue->buffer[queue->tail] = *item;
  queue->tail = (queue->tail + 1) % queue->capacity;
  queue->length++;

  return true;
}

/**
 * @brief Pop front element from queue array
 *
 * @param queue
 * @param item
 * @return true
 * @return false
 */
bool pop_queue_array(queue_array_t *queue, qtype_t *item) {
  if (is_empty_queue_array(queue)) return false;

  if (item) *item = queue->buffer[queue->head];

  queue->head = (queue->head + 1) % queue->capacity;
  queue->length--;

  return true;
}

/**
 * @brief Get element from the queue array object
 *
 * @param queue
 * @param item
 */
void get_queue_array(const queue_array_t *queue, qtype_t *item) {
  *item = queue->buffer[queue->head];
}

/**
 * @brief Get length of queue array
 *
 * @param queue
 * @return size_t
 */
size_t length_queue_array(const queue_array_t *queue) { return queue->length; }

/**
 * @brief Get the memory size of queue array object
 *
 * @param capacity
 * @return size_t
 */
size_t get_queue_array_memory_size(const size_t capacity) {
  return sizeof(queue_array_t *) + sizeof(queue_array_t) +
         sizeof(qtype_t) * capacity;
}
