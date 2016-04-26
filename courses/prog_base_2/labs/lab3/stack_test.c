#include "stack_test.h"
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>
#include "stack.h"

static void new_NewStack_CountZeroAndIsEmpty(void ** state)
{
    stack_t * stack = stack_new(10);
    int count = stack_get_count(stack);
    assert_int_equal(0, count);
    assert_int_equal(1, stack_is_empty(stack));
    stack_delete(stack);
}

static void push_PushOne_CountOne(void ** state)
{
    stack_t * stack = stack_new(10);
    char * hey = "hey";
    stack_push(stack, hey);
    int count = stack_get_count(stack);
    assert_int_equal(1, count);
    stack_delete(stack);
}

static void push_PushTwo_CountTwo(void ** state)
{
    stack_t * stack = stack_new(10);
    char * hey = "hey";
    stack_push(stack, hey);
    stack_push(stack, hey);
    int count = stack_get_count(stack);
    assert_int_equal(2, count);
    stack_delete(stack);
}

static void pop_PushTwoPop_ReturnedLast(void ** state)
{
    stack_t * stack = stack_new(10);
    char * hey = "hey";
    char * hey2 = "hey2";
    stack_push(stack, hey);
    stack_push(stack, hey2);
    char * recv = stack_pop(stack);
    assert_int_equal(hey2, recv);
    stack_delete(stack);
}

static void pop_PushPointer_PushedPointer(void ** state)
{
    stack_t * stack = stack_new(10);
    char * hey = "hey";
    stack_push(stack, hey);
    char * recv = stack_pop(stack);
    assert_int_equal(recv, hey);
    stack_delete(stack);
}

static void get_count__PushedFourPoppedTwo__CountTwo(void ** state)
{
    stack_t * stack = stack_new(10);
    char * hey = "hey";
    stack_push(stack, hey);
    stack_push(stack, hey);
    stack_push(stack, hey);
    stack_push(stack, hey);
    stack_pop(stack);
    stack_pop(stack);
    int count = stack_get_count(stack);
    assert_int_equal(2, count);
    stack_delete(stack);
}

static void push_NewStackSize2PushedThree_ErrorCode(void ** state)
{
    stack_t * stack = stack_new(2);
    char * hey = "hey";
    stack_push(stack, hey);
    stack_push(stack, hey);
    int err = stack_push(stack, hey);
    assert_int_equal(STACK_ERROR, err);
    stack_delete(stack);
}

static void pop_NewStackPop_ErrorCode(void ** state)
{
    stack_t * stack = stack_new(2);
    int err = stack_pop(stack);
    assert_int_equal(STACK_ERROR, err);
    stack_delete(stack);
}

void stack_test()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(new_NewStack_CountZeroAndIsEmpty),
        cmocka_unit_test(push_PushOne_CountOne),
        cmocka_unit_test(push_PushTwo_CountTwo),
        cmocka_unit_test(push_NewStackSize2PushedThree_ErrorCode),
        cmocka_unit_test(pop_NewStackPop_ErrorCode),
        cmocka_unit_test(pop_PushPointer_PushedPointer),
        cmocka_unit_test(pop_PushTwoPop_ReturnedLast),
        cmocka_unit_test(get_count__PushedFourPoppedTwo__CountTwo),

    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
