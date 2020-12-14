#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"
#include "input.h"

#define ITERATIONS 100

int compare_student(const void *a, const void *b);
void sort_student_table(struct student_table *table);

int compare_key(const void *key1, const void  *key2);
void sort_key_table(struct key_table *keys);

void swap_student(struct student *a, struct student *b);
void swap_keys(struct key *a, struct key *b);
void mysort_student(struct student *base, int n);
void mysort_keys(struct key *base, int n);

unsigned long long tick(void);
void measure_sorting_time(void);

#endif

