#ifndef INC_AVL_TREE_H_
#define INC_AVL_TREE_H_
/**
 * @file avl_tree.h
 * @author Vladimir Larin
 * @brief Avl tree container
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <stdbool.h>
#include <stdlib.h>

typedef char *avl_tree_type_t;
typedef int (*avl_tree_cmp_t)(avl_tree_type_t, avl_tree_type_t);

typedef struct avl_tree_node {
  avl_tree_type_t data;
  struct avl_tree_node *left;
  struct avl_tree_node *right;
  size_t height;
} avl_tree_node_t;

typedef struct avl_tree {
  avl_tree_node_t *head;
  avl_tree_cmp_t cmp;
} avl_tree_t;

bool add_avl_tree(avl_tree_t *tree, avl_tree_type_t element);

avl_tree_node_t *create_avl_tree_node(avl_tree_type_t element);

avl_tree_t *init_avl_tree(avl_tree_cmp_t cmp);

avl_tree_node_t *add_internel_avl_tree(avl_tree_node_t *node,
                                       avl_tree_type_t element,
                                       avl_tree_cmp_t cmp, size_t *cmps);

bool has_avl_tree_cmps(avl_tree_t *tree, avl_tree_type_t element,
                       size_t *cmps);
bool has_avl_tree(avl_tree_t *tree, avl_tree_type_t element);
size_t get_height_avl(avl_tree_node_t *node);

void fix_height(avl_tree_node_t *node);

int get_balance_avl_tree(avl_tree_node_t *node);

avl_tree_node_t *do_balance_avl_tree(avl_tree_node_t *node, size_t *cmps);

avl_tree_node_t *rotate_left_avl_tree(avl_tree_node_t *node);

avl_tree_node_t *rotate_right_avl_tree(avl_tree_node_t *node);
void destroy_avl_tree(avl_tree_node_t *node);
void free_avl_tree(avl_tree_t *tree);

void free_node_avl_tree(avl_tree_node_t *node);

typedef void (*avl_tree_walker_t)(avl_tree_node_t *parent,
                                  avl_tree_node_t *current);

int avl_tree_walker(avl_tree_t *tree, avl_tree_walker_t walker);

void avl_tree_walker_fn(avl_tree_node_t *node, avl_tree_walker_t walker);

bool add_avl_tree_cmps(avl_tree_t *tree, avl_tree_type_t element, size_t *cmps);
#endif  // INC_AVL_TREE_H_
