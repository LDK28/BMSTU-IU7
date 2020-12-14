#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

int compare_student(const void *a, const void *b)
{
    return ((struct student *)a)->age - ((struct student *)b)->age;
}

//по возрасту
void sort_student_table(struct student_table *table)
{
    qsort(table->pb, table->n, sizeof(struct student), compare_student);
}

int compare_key(const void *key1, const void  *key2)
{
    return ((struct key *)key1)->key - ((struct key *)key2)->key;
}

void sort_key_table(struct key_table *keys)
{
    qsort(keys->pb, keys->n, sizeof(struct key), compare_key);
}

void swap_student(struct student *a, struct student *b)
{
    struct student temp;
	
	temp = *a;
    *a = *b;
    *b = temp;
}

void swap_keys(struct key *a, struct key *b)
{
    struct key t = *a;
    *a = *b;
    *b = t;
}

void mysort_student(struct student *base, int n)
{
    struct student *pb = base;
    struct student *pe = pb + n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (pe - pb) - 1; j++)
            if (compare_student((void *)(pb + j), (void *)(pb + j + 1)) > 0)
                swap_student((pb + j), (pb + j + 1));
        pe--;
    }
}

void mysort_keys(struct key *base, int n)
{
    struct key *pb = base;
    struct key *pe = pb + n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (pe - pb) - 1; j++)
            if (compare_key((void *)(pb + j), (void *)(pb + j + 1)) > 0)
                swap_keys((pb + j), (pb + j + 1));
        pe--;
    }
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void measure_sorting_time(void)
{
    char name[LEN_NAME];
    struct student_table student_table = {NULL, 0, 0};
    struct key_table key_table = {NULL, 0};
    unsigned long long tm, t;
	int i;

    input_string("Input file name:\n", name, LEN_NAME);

    FILE *f = fopen(name, "r");

    if (!read_table_from_file(f, &student_table))
        printf("\nSuccessfully loaded\n");
    else
    {
        printf("\nCan't load\n");
        return;
    }
    printf("\n                   Table           Keys\n\n");

    printf("qsort   :");
    //qsort table
    t = 0;
    for (i = 0; i < ITERATIONS; i++)
    {
        tm = tick();
        sort_student_table(&student_table);
        tm = tick() - tm;
        t += tm;
        f = fopen(name, "r");
        read_table_from_file(f, &student_table);
        fclose(f);
    }
    printf("%15lld", t/ITERATIONS);

    //qsort table
    t = 0;

    for (i = 0; i < ITERATIONS; i++)
    {
        make_key_table(&student_table, &key_table);
        tm = tick();
        sort_key_table(&key_table);
        tm = tick() - tm;
        t += tm;
    }
    printf("%15lld", t/ITERATIONS);

    printf("\nmysort  :");
	
    // mysort table
    t = 0;

    for (i = 0; i < ITERATIONS; i++)
    {
        tm = tick();
        mysort_student(student_table.pb, student_table.n);
        tm = tick() - tm;
        t += tm;
        f = fopen(name, "r");
        read_table_from_file(f, &student_table);
        fclose(f);
    }
    printf("%15lld", t/ITERATIONS);

    // mysort key
    t = 0;

    for (i = 0; i < ITERATIONS; i++)
    {
        make_key_table(&student_table, &key_table);
        tm = tick();
        mysort_keys(key_table.pb, key_table.n);
        tm = tick() - tm;
        t += tm;
    }

    printf("%15lld\n", t/ITERATIONS);

    printf("\nsize    :%14zu B", sizeof(struct student) * student_table.n);
    printf("%13zu B\n", sizeof(struct key) * key_table.n);
    fclose(f);
}

