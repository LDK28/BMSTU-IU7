#ifndef POLINOM_H
#define POLINOM_H

#define __USE_MINGW_ANSI_STDIO 1

#define INCORRECT_ACTION_ERROR -1
#define INCORRECT_DATA_ERROR -2
#define ALLOCATE_ERROR -3


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum action
{
    VAL,
    DDX,
    SUM,
    DVD,
};

struct polinom
{
    long coefficient;
    long degree;

    struct polinom *next;
};

typedef struct polinom polinom_t;

void list_free_all(polinom_t *head);
int get_action(int *action);
int get_polinom(polinom_t **polinom);
void print_polinom(polinom_t *polinom);
long val(polinom_t *polinom, long number);
polinom_t *ddx(polinom_t *polinom);
polinom_t *sum(polinom_t *polinom1, polinom_t *polinom2);
int dvd(polinom_t *polinom, polinom_t **even, polinom_t **odd);

#endif
