#include <check.h>
#include <stdlib.h>
#include <check.h>
#include "main.c"

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


// negatives
START_TEST(test_sort_ten_null_pointer)
{    
    node_t *list = NULL;

    node_t *new_list = sort_ten(&list);

    ck_assert_ptr_null(new_list);
}
END_TEST

// positives
START_TEST(test_sort_ten_positive)
{
    long rc;
    node_t list;
    node_t *p = &list;
    list->previous = NULL;
    list->number = 5;
    node_t next_list;
    list->previous = &list;
    list->number = 101;
    node_t next_next_list;
    next_next_list->previous = &next_list;
    next_next_list->number = 109;

    list->next = &next_list;
    next_list->next = &next_next_list;

    node_t check_list;
    node_t *check_p = &list;
    check_list->previous = NULL;
    check_list->number = 101;
    node_t check_next_list;
    check_list->previous = &check_list;
    check_list->number = 109;
    node_t check_next_next_list;
    check_next_next_list->previous = &check_next_list;
    check_next_next_list->number = 5;

    check_list->next = &check_next_list;
    check_next_list->next = &check_next_next_list;


    node_t *new_list = sort_ten(&p);

    compare_lists(new_list, check_list);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_sort_ten_null_pointer);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_ten_positive);

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
