#include <check.h>
#include "films.h"

// negatives
START_TEST(test_count_films_empty_file)
{
    size_t rc;
    
    rc = count_films(NULL);

    ck_assert_int_eq(rc, 0);
}
END_TEST

// positives
START_TEST(test_check_field_year)
{
    char string[] = "year";
    long rc;

    rc = check_field(string);

    ck_assert_int_eq(rc, YEAR);
}
END_TEST

START_TEST(test_check_field_title)
{
    char string[] = "title";
    long rc;

    rc = check_field(string);

    ck_assert_int_eq(rc, TITLE);
}
END_TEST

START_TEST(test_check_field_name)
{
    char string[] = "name";
    long rc;

    rc = check_field(string);

    ck_assert_int_eq(rc, NAME);
}
END_TEST

START_TEST(test_check_field_empty)
{
    char string[] = "qwerty";
    long rc;

    rc = check_field(string);

    ck_assert_int_eq(rc, EMPTY);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_count_films_empty_file);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_check_field_year);
    tcase_add_test(tc_pos, test_check_field_name);
    tcase_add_test(tc_pos, test_check_field_title);
    tcase_add_test(tc_pos, test_check_field_empty);

    suite_add_tcase(s, tc_pos);

    return s;
}
