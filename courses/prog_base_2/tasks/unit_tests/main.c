#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>
#include "int_list.h"
static void int_list_insert_elements(void **state)
{
    int_list_t list = int_list_new();
    for(int i = 0; i < 100; i++)
    {
        int_list_insert(list, i, i);
    }
    for(int i = 99; i >= 0; i-=2)
        assert_int_equal(i, int_list_get_element(list, i));
}

static void int_list_remove_elements(void **state)
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

static void int_list_getPosCount(void **state)
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

static void int_list_getNegCount(void **state)
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

static void int_list_getZeroCount(void **state)
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
        cmocka_unit_test(int_list_insert_elements),
        cmocka_unit_test(int_list_remove_elements),
        cmocka_unit_test(int_list_getNegCount),
        cmocka_unit_test(int_list_getPosCount),
        cmocka_unit_test(int_list_getZeroCount)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
