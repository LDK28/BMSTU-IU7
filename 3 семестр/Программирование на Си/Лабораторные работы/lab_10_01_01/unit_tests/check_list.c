#include <check.h>
#include "list.h"

// negatives
START_TEST(test_pop_front_null_pointer)
{
    void *rc;
    node_t *list = NULL;

    rc = pop_front(&list);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_pop_back_null_pointer)
{
    void *rc;
    node_t *list = NULL;

    rc = pop_back(&list);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_pop_front_null_address_of_pointer)
{
    void *rc;

    rc = pop_front(NULL);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_pop_back_null_address_of_pointer)
{
    void *rc;

    rc = pop_back(NULL);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_pop_front_null_data)
{
    void *rc;
    node_t *list = malloc(sizeof(node_t));
    list->data = NULL;
    list->next = NULL;

    rc = pop_front(&list);

    ck_assert_ptr_null(rc);

    list_free_all(list);
}
END_TEST

START_TEST(test_pop_back_null_data)
{
    void *rc;
    node_t *list = malloc(sizeof(node_t));
    list->data = NULL;
    list->next = NULL;

    rc = pop_back(&list);

    ck_assert_ptr_null(rc);

    list_free_all(list);
}
END_TEST

START_TEST(test_append_two_null_pointer)
{
    node_t *head_a = NULL;
    node_t *head_b = NULL;

    append(&head_a, &head_b);

    ck_assert_ptr_null(head_a);
    ck_assert_ptr_null(head_b);
}
END_TEST

// positives

START_TEST(test_pop_front_cmp_results)
{
    void *rc;
    void *cmp;
    node_t *list = malloc(sizeof(node_t));
    list->data = malloc(sizeof(int));
    list->next = malloc(sizeof(node_t));
    list->next->data = malloc(sizeof(int));
    list->next->next = NULL;

    cmp = list->data;
    rc = pop_front(&list);

    ck_assert_ptr_eq(rc, cmp);

    free(cmp);
    list_free_all(list);
}
END_TEST

START_TEST(test_pop_back_cmp_results)
{
    void *rc;
    void *cmp;
    node_t *list = malloc(sizeof(node_t));
    list->data = malloc(sizeof(int));
    list->next = malloc(sizeof(node_t));
    list->next->data = malloc(sizeof(int));
    list->next->next = NULL;

    cmp = list->next->data;
    rc = pop_back(&list);

    ck_assert_ptr_eq(rc, cmp);

    free(cmp);
    list_free_all(list);
}
END_TEST

START_TEST(test_pop_back_long_list)
{
    void *rc;
    void *cmp;
    node_t *list = malloc(sizeof(node_t));
    node_t *cur = list;
    for (size_t i = 0; i < 15; ++i)
    {
        cur->data = malloc(sizeof(int));
        cur->next = malloc(sizeof(node_t));
        cur = cur->next;
    }
    cur->data = malloc(sizeof(int));
    cur->next = NULL;

    cmp = cur->data;
    rc = pop_back(&list);

    ck_assert_ptr_eq(rc, cmp);

    free(cmp);
    list_free_all(list);
}
END_TEST


START_TEST(test_append_null_head_a)
{
    node_t *head_a = NULL;
    node_t *head_b = malloc(sizeof(node_t));
    head_b->data = malloc(sizeof(int));
    head_b->next = NULL;
    node_t *tmp = head_b;

    append(&head_a, &head_b);

    ck_assert_ptr_null(head_b);
    ck_assert_ptr_eq(tmp, head_a);

    list_free_all(head_a);
}
END_TEST

START_TEST(test_append_standart_pointers)
{
    node_t *head_a = malloc(sizeof(node_t));
    head_a->data = malloc(sizeof(int));
    head_a->next = NULL;
    node_t *head_b = malloc(sizeof(node_t));
    head_b->data = malloc(sizeof(int));
    head_b->next = NULL;
    node_t *tmp = head_b;

    append(&head_a, &head_b);

    ck_assert_ptr_eq(head_a->next, tmp);
    ck_assert_ptr_null(head_b);

    list_free_all(head_a);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_pop_front_null_pointer);
    tcase_add_test(tc_neg, test_pop_back_null_pointer);
    tcase_add_test(tc_neg, test_pop_front_null_address_of_pointer);
    tcase_add_test(tc_neg, test_pop_back_null_address_of_pointer);
    tcase_add_test(tc_neg, test_pop_front_null_data);
    tcase_add_test(tc_neg, test_pop_back_null_data);
    tcase_add_test(tc_neg, test_append_two_null_pointer);
    

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_pop_front_cmp_results);
    tcase_add_test(tc_pos, test_pop_back_cmp_results);
    tcase_add_test(tc_pos, test_pop_back_long_list);
    tcase_add_test(tc_pos, test_append_null_head_a);
    tcase_add_test(tc_pos, test_append_standart_pointers);

    suite_add_tcase(s, tc_pos);

    return s;
}
