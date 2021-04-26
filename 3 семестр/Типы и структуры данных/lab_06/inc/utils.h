#ifndef INC_UTILS_H_
#define INC_UTILS_H_
/**
 * @file utils.c
 * @author Vladimir Larin
 * @brief Utils functions
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "inc/btree.h"

int clear_input();
int wait_and_clear();

void exit_handler();

int next_prime(int);
int strcmp_connector(btree_type_t a, btree_type_t b);

#endif  // INC_UTILS_H_
