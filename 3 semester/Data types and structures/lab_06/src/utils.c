/**
 * @file utils.c
 * @author Vladimir Larin
 * @brief Utils functions
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "inc/utils.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int clear_input() {
  int ch = 0;

  do {
    ch = getc(stdin);
  } while (ch != '\n');

  return 0;
}
int wait_and_clear() {
  printf("Нажмите <ENTER>, чтобы продолжить.\n");
  clear_input();
  system("clear");
  return 0;
}

void exit_handler() {
  printf("До скорой встречи!\n");
  system("rm -rf temp.txt temp.png");
  exit(0);
}

bool is_prime(int number) {
  if (number == 2 || number == 3) return true;

  if (number % 2 == 0 || number % 3 == 0) return false;

  int divisor = 6;
  while (divisor * divisor - 2 * divisor + 1 <= number) {
    if (number % (divisor - 1) == 0) return false;

    if (number % (divisor + 1) == 0) return false;

    divisor += 6;
  }

  return true;
}

int next_prime(int a) {
  while (!is_prime(a)) a++;
  return a;
}

int strcmp_connector(btree_type_t a, btree_type_t b) { return strcmp(a, b); }
