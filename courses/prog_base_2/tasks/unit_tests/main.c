#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>
#include "int_list.h"
static void new_CreatedListAddedTwoElements_SizeIsTwo(void ** state)
{
    int_list_t list = int_list_new();
    int_list_insert(list, 1, 0);
    int_list_insert(list, 1, 0);
    assert_int_equal(2, int_list_get_size(list));
}
static void new_CreatedList_SizeIsNull(void ** state)
{
    int_list_t * list = int_list_new();
    assert_int_equal(0, int_list_get_size(list));
}
static void insert_100ElementsSequence_DataAtIndexCorrect(void **state)
{
    int_list_t list = int_list_new();
    for(int i = 0; i < 100; i++)
    {
        int_list_insert(list, i, i);
    }
    for(int i = 99; i >= 0; i-=2)
        assert_int_equal(i, int_list_get_element(list, i));
}

static void remove_ThreeElementsDeleteFirst_CorrectValueAtFirst(void **state)
{
    int_list_t list = int_list_new();
    int_list_insert(list, 1, 0);
    int_list_insert(list, -1, 0);
    int_list_insert(list, -1, 0);
    int_list_remove(list, 0);
    assert_int_equal(-1, int_list_get_element(list, 0));
    int_list_remove(list, 0);
    assert_int_equal(1, int_list_get_element(list, 0));
    int_list_delete(list);
}

static void get_poscount__ThreePositiveOneNegative_ThenOnePositiveOneZero__CorrectNumberOfPositives(void **state)
{
    int_list_t list = int_list_new();
    int_list_insert(list, 1, 0);
    int_list_insert(list, 2, 0);
    int_list_insert(list, 3, 0);
    int_list_insert(list, -1, 0);
    assert_int_equal(3, int_list_get_poscount(list));
    int_list_insert(list, 3, 0);
    int_list_insert(list, 0, 0);
    assert_int_equal(4, int_list_get_poscount(list));
    int_list_delete(list);
}

static void get_negcount__ThreePositivesOneZero_ThenOnePositiveOneNegative__CorrectNumberOfNegatives(void **state)
{
    int_list_t list = int_list_new();
    int_list_insert(list, 1, 0);
    int_list_insert(list, 2, 0);
    int_list_insert(list, 3, 0);
    int_list_insert(list, -1, 0);
    assert_int_equal(1, int_list_get_negcount(list));
    int_list_insert(list, 3, 0);
    int_list_insert(list, -11, 0);
    assert_int_equal(2, int_list_get_negcount(list));
    int_list_delete(list);
}

static void get_zerocount__ThreePositivesOneNegative_ThenOnePositiveOneZero__CorrectNumberOfZeros(void **state)
{
    int_list_t list = int_list_new();
    int_list_insert(list, 1, 0);
    int_list_insert(list, 2, 0);
    int_list_insert(list, 3, 0);
    int_list_insert(list, -1, 0);
    assert_int_equal(0, int_list_get_zerocount(list));
    int_list_insert(list, 3, 0);
    int_list_insert(list, 0, 0);
    assert_int_equal(1, int_list_get_zerocount(list));
    int_list_delete(list);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(insert_100ElementsSequence_DataAtIndexCorrect),
        cmocka_unit_test(remove_ThreeElementsDeleteFirst_CorrectValueAtFirst),
        cmocka_unit_test(get_negcount__ThreePositivesOneZero_ThenOnePositiveOneNegative__CorrectNumberOfNegatives),
        cmocka_unit_test(get_poscount__ThreePositiveOneNegative_ThenOnePositiveOneZero__CorrectNumberOfPositives),
        cmocka_unit_test(get_zerocount__ThreePositivesOneNegative_ThenOnePositiveOneZero__CorrectNumberOfZeros),
        cmocka_unit_test(new_CreatedList_SizeIsNull),
        cmocka_unit_test(new_CreatedListAddedTwoElements_SizeIsTwo)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
