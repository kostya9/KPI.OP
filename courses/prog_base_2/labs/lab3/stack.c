#include "stack.h"
#include <stdlib.h>
#include <malloc.h>
struct stack_s{
    unsigned int top;
    size_t count_el;
    size_t size_arr;
    void ** arr;
};

stack_t * stack_new(size_t size)
{
    stack_t * list = malloc(sizeof(struct stack_s));
    if(list == NULL)
        return NULL;
    list->top = 0;
    list->count_el = 0;
    list->size_arr = size;
    list->arr = malloc(sizeof(void *) * size);
    if(list->arr == NULL)
    {
        free(list);
        return NULL;
    }
    return list;
}
void stack_delete(stack_t * self)
{
    free(self->arr);
    free(self);
}

int stack_push(stack_t * self, void * el)
{
    int index = self->count_el;
    if(index >= self->size_arr )
        return STACK_ERROR;
    self->arr[index] = el;
    (self->count_el)++;
    return STACK_OK;
}
void * stack_pop(stack_t * self)
{
    if(self->count_el < 1)
        return STACK_ERROR;

    void * el = self->arr[--(self->count_el)];

    return el;
}

int stack_get_count(stack_t * self)
{
    return self->count_el;
}

int stack_is_empty(stack_t * self)
{
    return self->count_el == 0;
}
