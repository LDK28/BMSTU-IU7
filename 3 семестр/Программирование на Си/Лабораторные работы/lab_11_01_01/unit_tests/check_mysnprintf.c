#include <check.h>
#include <string.h>
#include "mysnprintf.h"

START_TEST(test_c)
{
    char buf[20];
    char res_buf[20];
    int rc = my_snprintf(buf, 20, "44444 %c 6666", 'r');
    int res_rc = snprintf(res_buf, 20, "44444 %c 6666", 'r');
    int cmp = strcmp(buf, res_buf);

    ck_assert_int_eq(rc, res_rc);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

START_TEST(test_d_zero)
{
    char buf[20];
    char res_buf[20];
    int rc = my_snprintf(buf, 20, "44444 %d 6666", 0);
    int res_rc = snprintf(res_buf, 20, "44444 %d 6666", 0);
    int cmp = strcmp(buf, res_buf);

    ck_assert_int_eq(rc, res_rc);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

START_TEST(test_d_positive)
{
    char buf[20];
    char res_buf[20];
    int rc = my_snprintf(buf, 20, "44444 %d 6666", 12345);
    int res_rc = snprintf(res_buf, 20, "44444 %d 6666", 12345);
    int cmp = strcmp(buf, res_buf);

    ck_assert_int_eq(rc, res_rc);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

START_TEST(test_d_negative)
{
    char buf[20];
    char res_buf[20];
    int rc = my_snprintf(buf, 20, "44444 %d 6666", -12345);
    int res_rc = snprintf(res_buf, 20, "44444 %d 6666", -12345);
    int cmp = strcmp(buf, res_buf);

    ck_assert_int_eq(rc, res_rc);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

START_TEST(test_s)
{
    char buf[20];
    char res_buf[20];
    int rc = my_snprintf(buf, 10, "%s", "12345");
    int res_rc = snprintf(res_buf, 10, "%s", "12345");
    int cmp = strcmp(buf, res_buf);

    ck_assert_int_eq(rc, res_rc);
    ck_assert_int_eq(cmp, 0);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_c);
    tcase_add_test(tc_pos, test_d_zero);
    tcase_add_test(tc_pos, test_d_positive);
    tcase_add_test(tc_pos, test_d_negative);
    tcase_add_test(tc_pos, test_s);

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
