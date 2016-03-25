#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "matrix.h"
#include "vector.h"

// unit-test function
static void get_intArray_2AtPosition1(void **state)
{
    const int test_arr[3] = {1, 2, 3};
    vector_t * vector = vector_new(3, test_arr);
    int actual = vector_get_el(vector, 1);
    int expected = 2;
    vector_free(vector);
    assert_int_equal(actual, expected);
}
static void set_intArraySet3AtPosition1_3AtPosition1(void **state)
{
    const int test_arr[3][3] = {1, 2, 3};
    vector_t * vector = vector_new(3 ,test_arr);
    vector_set_el(vector, 1, 3);
    int actual = vector_get_el(vector, 1);
    int expected = 3;
    vector_free(vector);
    assert_int_equal(actual, expected);
}
static void multiply_vector__intArray__4AtPosition1(void **state)
{
    const int test_arr[3][3] = {1, 2, 3};
    vector_t * vector = vector_new(3 ,test_arr);
    vector_t * vector1 = vector_new(3 ,test_arr);
    vector_t * vector2 = vector_multiply_vector(vector, vector1);
    int actual = vector_get_el(vector2, 1);
    int expected = 4;
    vector_free(vector);
    vector_free(vector1);
    vector_free(vector2);
    assert_int_equal(actual, expected);
}
void vector_test() {
    puts("Testing vectors on vector \n\t1\n\t2\n\t3\n...");
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(get_intArray_2AtPosition1),
        cmocka_unit_test(set_intArraySet3AtPosition1_3AtPosition1),
        cmocka_unit_test(multiply_vector__intArray__4AtPosition1),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
