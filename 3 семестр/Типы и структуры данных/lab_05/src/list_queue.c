#include "list_queue.h"

#include <stdbool.h>
#include <stdlib.h>


static node_t *create_node(const qtype_t *item) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = *item;
  new_node->next = NULL;

  return new_node;
}

static void free_node(node_t *node) { free(node); }

static void free_list(node_t *head) {
  while (head) {
    node_t *next = head->next;
    free_node(head);
    head = next;
  }
}

queue_list_t *create_queue_list() {
  queue_list_t *queue = malloc(sizeof(queue_list_t));
  queue->head = queue->tail = NULL;
  queue->length = 0;

  return queue;
}

void empty_queue_list(queue_list_t *queue) {
  free_list(queue->head);
  queue->head = queue->tail = NULL;
  queue->length = 0;
}

void free_queue_list(queue_list_t *queue) {
  free_list(queue->head);
  free(queue);
}

bool is_empty_queue_list(const queue_list_t *queue) { return (!(queue->head)); }

bool push_queue_list(queue_list_t *queue, const qtype_t *item) {
  if (queue->tail) {
    queue->tail->next = create_node(item);
    queue->tail = queue->tail->next;
  } else {
    queue->tail = create_node(item);
    queue->head = queue->tail;
  }

  queue->tail->data.address = queue->tail;

  queue->length++;

  return true;
}

bool pop_queue_list(queue_list_t *queue, qtype_t *item) {
  if (is_empty_queue_list(queue)) {
    return false;
  }

  node_t *address = queue->head;

  if (item) {
    *item = queue->head->data;
  }

  if (!(queue->head = queue->head->next)) {
    queue->tail = NULL;
  }

  free_node(address);
  queue->length--;

  return true;
}

/**
 * @brief Get front element from queue list
 *
 * @param queue
 * @param item
 */
void get_queue_list(const queue_list_t *queue, qtype_t *item) {
  *item = queue->head->data;
}

/**
 * @brief Get the List Queue Length object
 *
 * @param queue
 * @return size_t
 */
size_t length_queue_list(const queue_list_t *queue) { return queue->length; }

/**
 * @brief Get memory size of the queue list
 *
 * @param length
 * @return size_t
 */
size_t get_queue_list_memory_size(const size_t length) {
  return sizeof(queue_list_t *) + sizeof(queue_list_t) +
         length * sizeof(node_t);
}
