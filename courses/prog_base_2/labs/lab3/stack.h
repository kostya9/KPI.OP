#pragma once
#include <stdlib.h>
#define STACK_ERROR 0
#define STACK_OK 1

typedef struct stack_s stack_t;

stack_t * stack_new(size_t size);
void stack_delete(stack_t * self);

int stack_push(stack_t * self, void * el);
void * stack_pop(stack_t * self);

int stack_get_count(stack_t * self);
int stack_is_empty(stack_t * self);
