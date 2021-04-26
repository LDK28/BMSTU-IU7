/*
 * Copyright 2020 Larin Vladimir
 * Binary tree container
 */

#include "inc/btree.h"

#include <stdio.h>

btree_node_t *create_bree_node(btree_type_t element) {
  btree_node_t *node = malloc(sizeof(*node));
  node->left = node->right = NULL;
  node->data = element;
  return node;
}
btree_t *init_btree(btree_cmp_t cmp) {
  btree_t *tree = malloc(sizeof(*tree));
  tree->head = NULL;
  tree->cmp = cmp;
  return tree;
}
void btree_free_node(btree_node_t *node) {
  if (!node) return;
  free(node->data);
  free(node);
}

void btree_free_walker(btree_node_t *parent, btree_node_t *current) {
  btree_free_node(current);
}

void btree_free(btree_t *tree) {
  if (!tree) return;
  btree_walker(tree, btree_free_walker);
  free(tree->head);
  free(tree);
}

btree_node_t *find_element_btree_cmps(btree_node_t *node, btree_type_t element,
                                      btree_cmp_t cmp, size_t *cmps) {
  int cmp_res = cmp(node->data, element);
  if (cmps) (*cmps)++;

  if (cmp_res > 0) {
    if (!node->right) return node;
    return find_element_btree_cmps(node->right, element, cmp, cmps);
  } else if (cmp_res < 0) {
    if (!node->left) return node;
    return find_element_btree_cmps(node->left, element, cmp, cmps);
  } else {
    return node;
  }
}

btree_node_t *find_element_btree(btree_node_t *node, btree_type_t element,
                                 btree_cmp_t cmp) {
  return find_element_btree_cmps(node, element, cmp, NULL);
}

bool add_btree_cmps(btree_t *tree, btree_type_t element, size_t *cmps) {
  if (!tree->head) {
    btree_node_t *node = create_bree_node(element);
    tree->head = node;
    return true;
  }

  btree_node_t *parent =
      find_element_btree_cmps(tree->head, element, tree->cmp, cmps);
  int cmp = tree->cmp(parent->data, element);
  if (cmps) (*cmps)++;
  if (!cmp) return false;

  btree_node_t *child_node = create_bree_node(element);
  if (cmp > 0)
    parent->right = child_node;
  else if (cmp < 0)
    parent->left = child_node;

  return true;
}

bool add_btree(btree_t *tree, btree_type_t element) {
  return add_btree_cmps(tree, element, NULL);
}

bool has_element_btree(btree_t *tree, btree_type_t element) {
  return has_element_btree_cmps(tree, element, NULL);
}

bool has_element_btree_cmps(btree_t *tree, btree_type_t element, size_t *cmps) {
  if (cmps) (*cmps)++;
  btree_node_t *node =
      find_element_btree_cmps(tree->head, element, tree->cmp, cmps);
  int cmp = tree->cmp(node->data, element);
  return !cmp;
}

typedef void (*btree_walker_t)(btree_node_t *parent, btree_node_t *current);

int btree_walker(btree_t *tree, btree_walker_t walker) {
  btree_walker_fn(tree->head, walker);
  return 0;
}

void btree_walker_fn(btree_node_t *node, btree_walker_t walker) {
  if (!node) return;

  btree_walker_fn(node->left, walker);
  btree_walker_fn(node->right, walker);

  if (node->left) walker(node, node->left);
  if (node->right) walker(node, node->right);

  return;
}
