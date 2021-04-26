/**
 * @file hash_table.h
 * @author Vladimir Larin (volodyalarin@bk.ru)
 * @brief Hash table container
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef INC_HASH_TABLE_H_
#define INC_HASH_TABLE_H_
#include <stdbool.h>
#include <stdlib.h>

typedef char *hash_type_t;
typedef int (*hash_func_t)(hash_type_t);
typedef int (*hash_cmp_t)(hash_type_t, hash_type_t);

typedef struct hash_table_node {
  hash_type_t data;
  struct hash_table_node *next;
} hash_table_node_t;

typedef struct hash_table {
  size_t max_collision_num;
  size_t elements_count;

  hash_func_t hasher;
  hash_cmp_t cmp;

  hash_table_node_t **table;
  size_t table_size;
} hash_table_t;

hash_table_t *init_hash_table(size_t, hash_func_t, hash_cmp_t);

hash_table_node_t *create_node(hash_type_t element);

void free_node(hash_table_node_t *node);

bool add_element_hash_table(hash_table_t *table, hash_type_t element);

bool has_element_hash_table(hash_table_t *table, hash_type_t element);

size_t len_list(hash_table_node_t *list);

int restruct_hash_table(hash_table_t **table, size_t new_table_size,
                        hash_func_t hasher);
void free_hash_table(hash_table_t *table);

bool add_element_hash_table_cmps(hash_table_t *table, hash_type_t element,
                                 size_t *cmps);
bool has_element_hash_table_cmps(hash_table_t *table, hash_type_t element,
                                 size_t *cmps);
#endif  // INC_HASH_TABLE_H_
