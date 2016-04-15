#include "queue.h"
#include <limits.h>
#include <stdio.h>
typedef struct queue_s{
    size_t arr_size;
    size_t el_count;
    int * arr;
} queue_s;
queue_t * queue_new()
{
    queue_s * queue = malloc(sizeof(queue_s));
    queue->arr_size = 2;
    queue->el_count = 0;
    queue->arr = malloc(sizeof(int) * 2);
    return queue;
}
static int isFull(queue_t * self)
{
    return (self->el_count == self->arr_size);
}
void queue_enqueue(queue_t * self, int n)
{
    if(isFull(self))
    {
        self->arr = realloc(self->arr, sizeof(int) * self->arr_size * 2);
        self->arr_size = self->arr_size * 2;
    }
    self->arr[self->el_count] = n;
    (self->el_count)++;

}
static void shift_left(queue_t * self)
{
    for(int i = 1; i < self->el_count; i++)
    {
        self->arr[i - 1] = self->arr[i];
    }
}
int queue_dequeue(queue_t* self)
{
    int el;
    if(self->el_count == 0)
        return QUEUE_ERROR;
    el = self->arr[0];
    shift_left(self);
    (self->el_count)--;
    return el;
}
size_t queue_get_count(queue_t * self)
{
    return self->el_count;
}
int queue_peek(queue_t * self)
{
    if(self->el_count == 0)
        return QUEUE_ERROR;
    return self->arr[0];
}
void queue_delete(queue_t * self)
{
    free(self->arr);
    free(self);
}
int queue_is_empty(queue_t * self)
{
    return self->el_count == 0;
}
void queue_print(queue_t * self)
{
    puts("HEAD:");
    for(int i = 0; i < self->el_count; i++)
    {
        printf("%i\n", self->arr[i]);
    }
    puts(":TAIL");
}
