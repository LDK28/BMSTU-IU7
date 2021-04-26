#include <check.h>
#include "polinom.h"

int compare_polinoms(polinom_t *polinom1, polinom_t *polinom2)
{
    while (polinom1 && polinom2)
    {
        if (polinom1->coefficient != polinom2->coefficient || polinom1->degree != polinom2->degree)
            return -1;
        polinom1 = polinom1->next;
        polinom2 = polinom2->next;
    }
    if (polinom1 || polinom2)
        return -1;
    
    return 0;
}

// negatives
START_TEST(test_ddx_null_pointer)
{
    polinom_t *rc;

    rc = ddx(NULL);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_sum_both_null_pointer)
{
    polinom_t *rc;

    rc = sum(NULL, NULL);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_sum_empty_result)
{
    polinom_t *rc;

    polinom_t *polinom1 = malloc(sizeof(polinom_t));
    polinom1->coefficient = 4;
    polinom1->degree = 2;
    polinom1->next = NULL;

    polinom_t *polinom2 = malloc(sizeof(polinom_t));
    polinom2->coefficient = -4;
    polinom2->degree = 2;
    polinom2->next = NULL;

    rc = sum(polinom1, polinom2);

    ck_assert_ptr_null(rc);

    list_free_all(polinom1);
    list_free_all(polinom2);
}
END_TEST

// positives
START_TEST(test_val)
{
    long rc;
    long var = 7;
    long result = 197;
    polinom_t *polinom = malloc(sizeof(polinom_t));
    polinom->coefficient = 4;
    polinom->degree = 2;
    polinom->next = malloc(sizeof(polinom_t));
    polinom->next->coefficient = 1;
    polinom->next->degree = 0;
    polinom->next->next = NULL;

    rc = val(polinom, var);

    ck_assert_int_eq(rc, result);

    list_free_all(polinom);
}
END_TEST

START_TEST(test_ddx)
{
    long rc;
    polinom_t *polinom = malloc(sizeof(polinom_t));
    polinom->coefficient = 4;
    polinom->degree = 2;
    polinom->next = malloc(sizeof(polinom_t));
    polinom->next->coefficient = 12;
    polinom->next->degree = 1;
    polinom->next->next = malloc(sizeof(polinom_t));
    polinom->next->next->coefficient = 1;
    polinom->next->next->degree = 0;
    polinom->next->next->next = NULL;

    polinom_t *cmp = malloc(sizeof(polinom_t));
    cmp->coefficient = 8;
    cmp->degree = 1;
    cmp->next = malloc(sizeof(polinom_t));
    cmp->next->coefficient = 12;
    cmp->next->degree = 0;
    cmp->next->next = NULL;

    polinom_t *result = ddx(polinom);

    rc = compare_polinoms(cmp, result);

    ck_assert_int_eq(rc, 0);

    list_free_all(polinom);
    list_free_all(result);
    list_free_all(cmp);
}
END_TEST

START_TEST(test_sum)
{
    long rc;

    polinom_t *polinom1 = malloc(sizeof(polinom_t));
    polinom1->coefficient = 4;
    polinom1->degree = 2;
    polinom1->next = NULL;

    polinom_t *polinom2 = malloc(sizeof(polinom_t));
    polinom2->coefficient = 4;
    polinom2->degree = 2;
    polinom2->next = NULL;

    polinom_t *cmp = malloc(sizeof(polinom_t));
    cmp->coefficient = 8;
    cmp->degree = 2;
    cmp->next = NULL;

    polinom_t *result = sum(polinom1, polinom2);

    rc = compare_polinoms(cmp, result);

    ck_assert_int_eq(rc, 0);

    list_free_all(polinom1);
    list_free_all(polinom2);
    list_free_all(result);
    list_free_all(cmp);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_ddx_null_pointer);
    tcase_add_test(tc_neg, test_sum_both_null_pointer);
    tcase_add_test(tc_neg, test_sum_empty_result);
    
    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_val);
    tcase_add_test(tc_pos, test_ddx);
    tcase_add_test(tc_pos, test_sum);

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
