#include <check.h>
#include <stdlib.h>
#include <check.h>
#include "main.c"

typedef struct node
{
    struct node *previous;
    double number;
    struct node *next;
} node_t;

long compare_lists(node_t *head_a, node_t *head_b)
{
    node_t *first_a = head_a;
    node_t *first_b = head_b;

    while (head_a->next && head_b->next && head_a != first_a && head_b != first_b)
    {
        if (head_a->number != head_b->number)
            return head_a->number - head_b->number;
        head_a = head_a->next;
        head_b = head_b->next;
    }
    if (head_a)
        return 1;
    else if (head_b)
        return -1;
    else
        return 0;
}

void list_free_all(node_t *head)
{
    node_t *first = head;
    for (; head && head != first; head = head->next)
        free(head);
}


// negatives
START_TEST(test_append_average_null_pointer)
{    
    node_t *list = NULL;

    append_average(&list);

    ck_assert_ptr_null(list);
}
END_TEST

// positives
START_TEST(test_append_average_positive)
{
    long rc;
    node_t *list = malloc(sizeof(node_t));
    list->previous = NULL;

    node_t *cur = list;
    for (size_t i = 1; i < 4; ++i)
    {
        cur->number = i;
        cur->next = malloc(sizeof(node_t));
        cur->next->previous = cur;
        cur = cur->next;
    }
    cur->next = NULL;
    cur->number = 4;

    node_t *list_check = malloc(sizeof(node_t));
    list_check->previous = NULL;

    node_t *cur = list_check;
    for (size_t i = 1; i < 5; ++i)
    {
        cur->next = malloc(sizeof(node_t));
        cur->next->previous = cur;
        cur = cur->next;
    }
    cur->next = NULL;
    cur->number = 4;

    list_check->number = 1;
    list_check->next->number = 2;
    list_check->next->next->number = 2.5;
    list_check->next->next->next->number = 3;
    list_check->next->next->next->next->number = 4;

    append_average(&list);

    compare_lists(list, list_check);

    list_free_all(list);
    list_free_all(list_check);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_append_average_null_pointer);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_check_field_year);

    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = funcs_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
