#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_SURNAME 31
#define LEN_NAME 31
#define LEN_STREET 31

#define STEP 10

#define NO_ERR 0
#define ERR_PARAM -1
#define ERR_ID -2
#define ERR_STRUCT -3
#define ERR_READ -3
#define ERR_SIZE -5
#define ERR_FILE -6
#define INCORRECT_DATA_ERROR -7

typedef struct student
{
    char name[LEN_NAME];
	char surname[LEN_SURNAME];
    int gender; // 0 - female 1 - male
    int age;
	int group;
    int average_grade;
    int admission_year;
    int house_type; // 0 - home 1 - hostel

    union
    {
        struct {
            char street[LEN_STREET];
            int house;
            int flat;
        } home;

        struct {
            int hostel_num;
            int room;
        } hostel;

    } adress;
} student_t;

typedef struct student_table
{
    struct student *pb;
    int n;
    int max_n;
} student_table_t;

struct key
{
        int key;
        int id;
}key;

typedef struct key_table
{
        struct key *pb;
        int n;
} key_table_t;

void input_student(struct student *student);
void output_student(struct student student);
int read_student_from_file(FILE *f, student_t *student);
void write_student_to_file(FILE *f, struct student student);

void clear_table(struct student_table *table);
int add_to_table(struct student_table *table, const struct student *student);
int remove_from_table(struct student_table *table, int i);
int read_table_from_file(FILE *f, struct student_table *table);
void write_table_to_file(FILE *f, struct student_table *table);
void output_table(struct student_table *table);
void print_table_from_file(FILE *f);

void clear_key_table(struct key_table *keys);
int make_key_table(struct student_table *table, struct key_table *keys);
void print_key_table(const struct key_table *keys);
int print_student_table_by_key(const struct student_table *table, const struct key_table *keys);

void search(struct student_table *table);

#endif

