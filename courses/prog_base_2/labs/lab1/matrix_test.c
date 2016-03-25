#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "matrix.h"
#include "vector.h"

// unit-test function
static void get_intArray_2AtPosition0x1(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    int actual = matrix_get_el(matrix, 0, 1);
    int expected = 2;
    matrix_free(matrix);
    assert_int_equal(actual, expected);
}
static void set_intArraySet3AtPosition1_3AtPosition0x1(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    matrix_set_el(matrix, 0, 1, 3);
    int actual = matrix_get_el(matrix, 0, 1);
    int expected = 3;
    matrix_free(matrix);
    assert_int_equal(actual, expected);
}
static void get_last_error__setAtNotExistingIndex__ERROR_INCORRECT_DIMENSIONS(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    matrix_set_el(matrix, 4, 4, 3);
    int actual = matrix_get_last_error();
    int expected = MATRIX_ERROR_INCORRECT_DIMENSIONS;
    matrix_free(matrix);
    assert_int_equal(actual, expected);
}
static void multiply_intArrays_96AtPosiiton1x2(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    matrix_t * matrix1 = matrix_new(3, 3, test_arr);
    matrix_t * matrix2 = matrix_multiply(matrix, matrix1);
    int actual = matrix_get_el(matrix2, 1, 2);
    int expected = 96;
    matrix_free(matrix);
    matrix_free(matrix1);
    matrix_free(matrix2);
    assert_int_equal(actual, expected);
}
static void multiply_elwise__intArrays__36AtPosiiton1x2(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    matrix_t * matrix1 = matrix_new(3, 3, test_arr);
    matrix_t * matrix2 = matrix_multiply_elwise(matrix, matrix1);
    int actual = matrix_get_el(matrix2, 1, 2);
    int expected = 36;
    matrix_free(matrix);
    matrix_free(matrix1);
    matrix_free(matrix2);
    assert_int_equal(actual, expected);
}
static void add_intArrays_12AtPosiiton1x2(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    matrix_t * matrix1 = matrix_new(3, 3, test_arr);
    matrix_t * matrix2 = matrix_add(matrix, matrix1);
    int actual = matrix_get_el(matrix2, 1, 2);
    int expected = 12;
    matrix_free(matrix);
    matrix_free(matrix1);
    matrix_free(matrix2);
    assert_int_equal(actual, expected);
}
static void transpose_intArray_8AtPosiiton1x2(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    matrix_t * matrix1 = matrix_transpose(matrix);
    int actual = matrix_get_el(matrix1, 1, 2);
    int expected = 8;
    matrix_free(matrix);
    matrix_free(matrix1);
    assert_int_equal(actual, expected);
}
static void multiply_vector__intArrays__50AtPosiiton0x2(void **state)
{
    const int test_arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_t * matrix = matrix_new(3, 3, test_arr);
    vector_t * vector = vector_new(3, test_arr);
    matrix_t * matrix2 = matrix_multiply_vector(matrix, vector);
    int actual = matrix_get_el(matrix2, 2, 0);
    int expected = 50;
    matrix_free(matrix);
    vector_free(vector);
    matrix_free(matrix2);
    assert_int_equal(actual, expected);
}
void matrix_test() {
    puts("Testing on matrix 3x3\n 1 2 3\n 4 5 6\n 7 8 9\n...");
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(get_intArray_2AtPosition0x1),
        cmocka_unit_test(set_intArraySet3AtPosition1_3AtPosition0x1),
        cmocka_unit_test(get_last_error__setAtNotExistingIndex__ERROR_INCORRECT_DIMENSIONS),
        cmocka_unit_test(multiply_intArrays_96AtPosiiton1x2),
        cmocka_unit_test(multiply_elwise__intArrays__36AtPosiiton1x2),
        cmocka_unit_test(add_intArrays_12AtPosiiton1x2),
        cmocka_unit_test(transpose_intArray_8AtPosiiton1x2),
        cmocka_unit_test(multiply_vector__intArrays__50AtPosiiton0x2),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
