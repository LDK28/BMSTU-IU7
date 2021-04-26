/*
 * Copyright 2020 Larin Vladimir
 * Hash table container
 */
#include "inc/hash_table.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

hash_table_t *init_hash_table(size_t table_size, hash_func_t hasher,
                              hash_cmp_t cmp) {
  hash_table_t *hash_table = malloc(sizeof(*hash_table));

  hash_table->hasher = hasher;
  hash_table->cmp = cmp;
  hash_table->table_size = table_size;
  hash_table->max_collision_num = 0;
  hash_table->elements_count = 0;
  hash_table->table = calloc(sizeof(*hash_table->table), table_size);

  return hash_table;
}

hash_table_node_t *create_node(hash_type_t element) {
  hash_table_node_t *node = malloc(sizeof(*node));
  node->data = element;
  node->next = NULL;
  return node;
}

void free_node(hash_table_node_t *node) {
  if (!node) return;
  free(node->data);
  free(node);
}

bool add_element_hash_table_cmps(hash_table_t *table, hash_type_t element,
                                 size_t *cmps) {
  size_t pos = table->hasher(element) % table->table_size;

  if (has_element_hash_table(table, element)) return false;
  hash_table_node_t *node = create_node(element);
  (table->elements_count)++;

  node->next = table->table[pos];
  table->table[pos] = node;

  size_t len = len_list(table->table[pos]);
  if (table->max_collision_num < len) table->max_collision_num = len;
  if (cmps) (*cmps) += len;
  return true;
}
bool add_element_hash_table(hash_table_t *table, hash_type_t element) {
  return add_element_hash_table_cmps(table, element, NULL);
}

bool has_element_hash_table(hash_table_t *table, hash_type_t element) {
  return has_element_hash_table_cmps(table, element, NULL);
}

bool has_element_hash_table_cmps(hash_table_t *table, hash_type_t element,
                                 size_t *cmps) {
  size_t pos = table->hasher(element) % table->table_size;

  hash_table_node_t *node = table->table[pos];

  while (node) {
    int cmp = table->cmp(node->data, element);
    if (cmps) (*cmps)++;

    if (!cmp) return true;
    node = node->next;
  }

  return false;
}

size_t len_list(hash_table_node_t *list) {
  hash_table_node_t *node = list;
  size_t len = 0;
  while (node) {
    len++;
    node = node->next;
  }
  return len;
}

int restruct_hash_table(hash_table_t **table, size_t new_table_size,
                        hash_func_t hasher) {
  hash_table_t *new = init_hash_table(new_table_size, hasher, (*table)->cmp);

  for (size_t i = 0; i < (*table)->table_size; i++) {
    hash_table_node_t *node = (*table)->table[i];
    while (node) {
      add_element_hash_table(new, strdup(node->data));
      node = node->next;
    }
  }

  free_hash_table(*table);
  *table = new;
  return 0;
}

void free_hash_table(hash_table_t *table) {
  if (!table) return;

  for (size_t i = 0; i < table->table_size; i++) {
    hash_table_node_t *node = table->table[i];
    while (node) {
      hash_table_node_t *tmp = node;
      node = node->next;
      free_node(tmp);
    }
  }
  free(table->table);
  free(table);
}
