/**
 * @file avl_tree.c
 * @author Vladimir Larin
 * @brief Avl tree container
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "inc/avl_tree.h"

#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

bool add_avl_tree(avl_tree_t *tree, avl_tree_type_t element) {
  return add_avl_tree_cmps(tree, element, NULL);
}

bool add_avl_tree_cmps(avl_tree_t *tree, avl_tree_type_t element,
                       size_t *cmps) {
  tree->head = add_internel_avl_tree(tree->head, element, tree->cmp, cmps);
  return true;
}

avl_tree_node_t *create_avl_tree_node(avl_tree_type_t element) {
  avl_tree_node_t *node = malloc(sizeof(*node));
  node->left = node->right = NULL;
  node->data = element;
  node->height = 1;
  return node;
}

avl_tree_t *init_avl_tree(avl_tree_cmp_t cmp) {
  avl_tree_t *tree = malloc(sizeof(*tree));
  tree->head = NULL;
  tree->cmp = cmp;
  return tree;
}

avl_tree_node_t *add_internel_avl_tree(avl_tree_node_t *node,
                                       avl_tree_type_t element,
                                       avl_tree_cmp_t cmp, size_t *cmps) {
  if (!node) return create_avl_tree_node(element);

  int cmp_res = cmp(node->data, element);
  if (cmps) (*cmps)++;
  if (!cmp_res) return node;
  if (cmp_res < 0)
    node->right = add_internel_avl_tree(node->right, element, cmp, cmps);
  else
    node->left = add_internel_avl_tree(node->left, element, cmp, cmps);
  fix_height(node);
  return do_balance_avl_tree(node, cmps);
}

bool has_avl_tree_cmps(avl_tree_t *tree, avl_tree_type_t element,
                       size_t *cmps) {
  avl_tree_node_t *cur = tree->head;
  while (cur) {
    int cmp = tree->cmp(cur->data, element);
    if (cmps) (*cmps)++;

    if (!cmp) return true;

    if (cmp < 0)
      cur = cur->right;
    else
      cur = cur->left;
  }
  return false;
}

bool has_avl_tree(avl_tree_t *tree, avl_tree_type_t element) {
  return has_avl_tree_cmps(tree, element, NULL);
}

size_t get_height_avl(avl_tree_node_t *node) { return node ? node->height : 0; }

void fix_height(avl_tree_node_t *node) {
  node->height =
      max(get_height_avl(node->left), get_height_avl(node->right)) + 1;
}

int get_balance_avl_tree(avl_tree_node_t *node) {
  size_t right = get_height_avl(node->right);
  size_t left = get_height_avl(node->left);
  return right - left;
}

avl_tree_node_t *do_balance_avl_tree(avl_tree_node_t *node, size_t *cmps) {
  fix_height(node);
  if (cmps) (*cmps) += 2;
  switch (get_balance_avl_tree(node)) {
    case 2: {
      if (get_balance_avl_tree(node->right) < 0)
        node->right = rotate_right_avl_tree(node->right);
      return rotate_left_avl_tree(node);
    }
    case -2: {
      if (get_balance_avl_tree(node->left) > 0)
        node->left = rotate_left_avl_tree(node->left);
      return rotate_right_avl_tree(node);
    }
    default:
      return node;
  }
}

avl_tree_node_t *rotate_left_avl_tree(avl_tree_node_t *node) {
  avl_tree_node_t *tmp = node->right;
  node->right = tmp->left;
  tmp->left = node;
  fix_height(node);
  fix_height(tmp);
  return tmp;
}

avl_tree_node_t *rotate_right_avl_tree(avl_tree_node_t *node) {
  avl_tree_node_t *tmp = node->left;
  node->left = tmp->right;
  tmp->right = node;
  fix_height(node);
  fix_height(tmp);
  return tmp;
}
void free_avl_tree(avl_tree_t *tree) {
  if (!tree) return;
  destroy_avl_tree(tree->head);
}

void destroy_avl_tree(avl_tree_node_t *node) {
  if (node) {
    destroy_avl_tree(node->left);
    destroy_avl_tree(node->right);
    free_node_avl_tree(node);
  }
}

void free_node_avl_tree(avl_tree_node_t *node) {
  if (!node) return;
  free(node->data);
  free(node);
}

typedef void (*avl_tree_walker_t)(avl_tree_node_t *parent,
                                  avl_tree_node_t *current);

int avl_tree_walker(avl_tree_t *tree, avl_tree_walker_t walker) {
  avl_tree_walker_fn(tree->head, walker);
  return 0;
}

void avl_tree_walker_fn(avl_tree_node_t *node, avl_tree_walker_t walker) {
  if (!node) return;

  avl_tree_walker_fn(node->left, walker);
  avl_tree_walker_fn(node->right, walker);

  if (node->left) walker(node, node->left);
  if (node->right) walker(node, node->right);

  return;
}
