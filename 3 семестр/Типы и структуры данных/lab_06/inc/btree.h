#ifndef INC_BTREE_H_
#define INC_BTREE_H_
/*
 * Copyright 2020 Larin Vladimir
 * Binary tree container
 */

#include <stdbool.h>
#include <stdlib.h>

typedef char *btree_type_t;
typedef int (*btree_cmp_t)(btree_type_t, btree_type_t);

typedef struct btree_node {
  btree_type_t data;
  struct btree_node *left;
  struct btree_node *right;
} btree_node_t;

typedef struct tree {
  btree_node_t *head;
  btree_cmp_t cmp;
} btree_t;

btree_t *init_btree(btree_cmp_t cmp);
void btree_free(btree_t *tree);

bool add_btree(btree_t *tree, btree_type_t element);

btree_node_t *find_element_btree(btree_node_t *node, btree_type_t element,
                                 btree_cmp_t cmp);

bool has_element_btree(btree_t *tree, btree_type_t element);

typedef void (*btree_walker_t)(btree_node_t *parent, btree_node_t *current);

void print_dot_btree_walker(btree_node_t *parent, btree_node_t *current);
int btree_walker(btree_t *tree, btree_walker_t walker);

void btree_walker_fn(btree_node_t *node, btree_walker_t walker);

bool add_btree_cmps(btree_t *tree, btree_type_t element, size_t *cmps);
bool has_element_btree_cmps(btree_t *tree, btree_type_t element, size_t *cmps);

#endif  // INC_BTREE_H_
