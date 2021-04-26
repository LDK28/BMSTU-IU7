#include <check.h>
#include "matrix.h"
#include "matrix_change.h"
#include "matrix_multiplication.h"

int compare_matrix(long **matrix1, long **matrix2, size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; ++i)
        for (size_t j = 0; j < columns; ++j)
            if (*(*(matrix1 + i) + j) != *(*(matrix2 + i) + j))
                return *(*(matrix1 + i) + j) - *(*(matrix2 + i) + j);
    return 0;
}

// negatives
START_TEST(test_reallocate_matrix_NULL_pointer)
{
    long **rc;

    rc = reallocate_matrix(NULL, 0, 0, 0, 0);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_output_matrix_NULL_pointer)
{
    long rc;

    rc = output_matrix(NULL, 0, 0);

    ck_assert_int_eq(rc, INCORRECT_POINTER_ERROR);
}
END_TEST

START_TEST(test_make_square_matrix_NULL_pointer)
{
    long rc;
    long **inp = NULL;
    size_t lines = 0, columns = 0; 

    rc = make_square_matrix(&inp, &lines, &columns);

    ck_assert_int_eq(rc, INCORRECT_POINTER_ERROR);
}
END_TEST

START_TEST(test_add_elements_NULL_pointer)
{
    long rc;
    long **inp = NULL;
    size_t lines = 0, columns = 0; 

    rc = add_elements(&inp, &lines, &columns);

    ck_assert_int_eq(rc, INCORRECT_POINTER_ERROR);
}
END_TEST

START_TEST(test_matrix_multiplication_NULL_pointer)
{
    long **rc;

    rc = matrix_multiplication(NULL, 0, 0, NULL, 0, 0);

    ck_assert_ptr_null(rc);
}
END_TEST

START_TEST(test_matrix_multiplication_columns_lines)
{
    long **rc;
    long **matrix1;
    matrix1 = allocate_matrix(1, 1);
    *(*(matrix1 + 0) + 0) = 0;

    long **matrix2;
    matrix2 = allocate_matrix(2, 2);
    *(*(matrix2 + 0) + 0) = 0;
    *(*(matrix2 + 0) + 1) = 0;
    *(*(matrix2 + 1) + 0) = 0;
    *(*(matrix2 + 1) + 1) = 0;

    rc = matrix_multiplication(matrix1, 1, 1, matrix2, 2, 2);

    ck_assert_ptr_null(rc);
    free_matrix(matrix1, 1);
    free_matrix(matrix2, 2);
}
END_TEST

// positives
START_TEST(test_make_square_matrix_columns_more_than_lines)
{
    long rc;
    long cmp;
    long **matrix1;
    size_t lines = 2, columns = 3;
    matrix1 = allocate_matrix(lines, columns);
    *(*(matrix1 + 0) + 0) = 4;
    *(*(matrix1 + 0) + 1) = 7;
    *(*(matrix1 + 0) + 2) = 1;
    *(*(matrix1 + 1) + 0) = 3;
    *(*(matrix1 + 1) + 1) = 2;
    *(*(matrix1 + 1) + 2) = 7;
    
    long **matrix2;
    matrix2 = allocate_matrix(2, 2);
    *(*(matrix2 + 0) + 0) = 4;
    *(*(matrix2 + 0) + 1) = 1;
    *(*(matrix2 + 1) + 0) = 3;
    *(*(matrix2 + 1) + 1) = 7;

    rc = make_square_matrix(&matrix1, &lines, &columns);
    cmp = compare_matrix(matrix1, matrix2, 2, 2);

    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(cmp, 0);
    free_matrix(matrix1, lines);
    free_matrix(matrix2, 2);
}
END_TEST

START_TEST(test_make_square_matrix_lines_more_than_columns)
{
    long rc;
    long cmp;
    long **matrix1;
    size_t lines = 5, columns = 3;
    matrix1 = allocate_matrix(lines, columns);
    *(*(matrix1 + 0) + 0) = 0;
    *(*(matrix1 + 0) + 1) = 2;
    *(*(matrix1 + 0) + 2) = 9;
    *(*(matrix1 + 1) + 0) = 1;
    *(*(matrix1 + 1) + 1) = 2;
    *(*(matrix1 + 1) + 2) = 2;
    *(*(matrix1 + 2) + 0) = 3;
    *(*(matrix1 + 2) + 1) = 3;
    *(*(matrix1 + 2) + 2) = 3;
    *(*(matrix1 + 3) + 0) = 8;
    *(*(matrix1 + 3) + 1) = 8;
    *(*(matrix1 + 3) + 2) = 2;
    *(*(matrix1 + 4) + 0) = 1;
    *(*(matrix1 + 4) + 1) = 8;
    *(*(matrix1 + 4) + 2) = 3;
    
    long **matrix2;
    matrix2 = allocate_matrix(3, 3);
    *(*(matrix2 + 0) + 0) = 1;
    *(*(matrix2 + 0) + 1) = 2;
    *(*(matrix2 + 0) + 2) = 2;
    *(*(matrix2 + 1) + 0) = 3;
    *(*(matrix2 + 1) + 1) = 3;
    *(*(matrix2 + 1) + 2) = 3;
    *(*(matrix2 + 2) + 0) = 1;
    *(*(matrix2 + 2) + 1) = 8;
    *(*(matrix2 + 2) + 2) = 3;

    rc = make_square_matrix(&matrix1, &lines, &columns);
    cmp = compare_matrix(matrix1, matrix2, 3, 3);

    ck_assert_int_eq(rc, EXIT_SUCCESS);
    ck_assert_int_eq(cmp, 0);
    free_matrix(matrix1, lines);
    free_matrix(matrix2, 3);
}
END_TEST

Suite* funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("funcs");
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_reallocate_matrix_NULL_pointer);
    tcase_add_test(tc_neg, test_output_matrix_NULL_pointer);
    tcase_add_test(tc_neg, test_make_square_matrix_NULL_pointer);
    tcase_add_test(tc_neg, test_add_elements_NULL_pointer);
    tcase_add_test(tc_neg, test_matrix_multiplication_NULL_pointer);
    tcase_add_test(tc_neg, test_matrix_multiplication_columns_lines);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_make_square_matrix_columns_more_than_lines);
    tcase_add_test(tc_pos, test_make_square_matrix_lines_more_than_columns);

    suite_add_tcase(s, tc_pos);

    return s;
}
