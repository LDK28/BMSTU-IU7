#include <check.h>
#include "dynamics.h"

int compare_array(const int *pa_src, const int *pb_src, const int *pa_dst, const int *pb_dst)
{
    size_t i;
    for (i = 0; pa_src + i != pb_src && pa_dst + i != pb_dst; ++i)
    {
        int rc = *(pa_src + i) - *(pa_dst + i);
        if (rc != 0)
            return rc;
    }
    if (pa_src + i != pb_src)
        return *(pa_src + i);
    if (pa_dst + i != pb_dst)
        return *(pa_dst + i);
    return 0;
}

START_TEST(test_key_NULL_pointer)
{
    int rc;
    int *pa_dst = NULL, *pb_dst = NULL;

    rc = key(NULL, NULL, &pa_dst, &pb_dst);
    free(pa_dst);

    ck_assert_int_eq(rc, INCORRECT_DYNAMICS_ERROR);
}
END_TEST

START_TEST(test_key_one_element_array)
{
    int rc;
    int array[] = {1};
    int *pa_src = array, *pb_src = pa_src + 1;
    int *pa_dst = NULL, *pb_dst = NULL;

    rc = key(pa_src, pb_src, &pa_dst, &pb_dst);
    free(pa_dst);

    ck_assert_int_eq(rc, INCORRECT_DATA_ERROR);
}
END_TEST

START_TEST(test_key_empty_future_array)
{
    int rc;
    int array[] = {5, 5, 5, 5, 5};
    int *pa_src = array, *pb_src = pa_src  + 5;
    int *pa_dst = NULL, *pb_dst = NULL;

    rc = key(pa_src, pb_src, &pa_dst, &pb_dst);
    free(pa_dst);

    ck_assert_int_eq(rc, INCORRECT_DATA_ERROR);
}
END_TEST

START_TEST(test_key_sorted_array)
{
    int rc, cmp;
    int array[] = {1, 2, 3, 4, 5};
    int *pa_src = array, *pb_src = pa_src  + 5;
    int *pa_dst = NULL, *pb_dst = NULL;

    int result_array[] = {2, 3, 4};
    int *pa = result_array, *pb = pa + 3;

    rc = key(pa_src, pb_src, &pa_dst, &pb_dst);
    cmp = compare_array(pa_dst, pb_dst, pa, pb);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(cmp, 0);
    free(pa_dst);
}
END_TEST

START_TEST(test_key_reversed_array)
{
    int rc, cmp;
    int array[] = {5, 4, 3, 2, 1};
    int *pa_src = array, *pb_src = pa_src  + 5;
    int *pa_dst = NULL, *pb_dst = NULL;

    int result_array[] = {4, 3, 2};
    int *pa = result_array, *pb = pa + 3;

    rc = key(pa_src, pb_src, &pa_dst, &pb_dst);
    cmp = compare_array(pa_dst, pb_dst, pa, pb);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(cmp, 0);
    free(pa_dst);
}
END_TEST

START_TEST(test_mysort_sorted_array)
{
    int cmp;
    int array[] = {1, 2, 3, 4, 5};
    int *pa_src = array, *pb_src = pa_src + 5;
    size_t len = 5;

    int result_array[] = {1, 2, 3, 4, 5};
    int *pa = result_array, *pb = pa + 5;

    mysort(pa_src, len, sizeof(int), compare);
    cmp = compare_array(pa_src, pb_src, pa, pb);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

START_TEST(test_mysort_reversed_array)
{
    int cmp;
    int array[] = {5, 4, 3, 2, 1};
    int *pa_src = array, *pb_src = pa_src + 5;
    size_t len = 5;

    int result_array[] = {1, 2, 3, 4, 5};
    int *pa = result_array, *pb = pa + 5;

    mysort(pa_src, len, sizeof(int), compare);
    cmp = compare_array(pa_src, pb_src, pa, pb);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_key_NULL_pointer);
    tcase_add_test(tc_neg, test_key_one_element_array);
    tcase_add_test(tc_neg, test_key_empty_future_array);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key_sorted_array);
    tcase_add_test(tc_pos, test_key_reversed_array);
    tcase_add_test(tc_pos, test_mysort_sorted_array);
    tcase_add_test(tc_pos, test_mysort_reversed_array);

    suite_add_tcase(s, tc_pos);

    return s;
}