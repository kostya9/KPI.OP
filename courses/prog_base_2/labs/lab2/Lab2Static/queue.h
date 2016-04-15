#pragma once
#include <limits.h>
#include <stdlib.h>
#define QUEUE_ERROR INT_MIN
typedef struct queue_s queue_t;


queue_t * queue_new();
void queue_enqueue(queue_t * self, int n);
int queue_dequeue(queue_t* self);
int queue_peek(queue_t * self);
int queue_is_empty(queue_t * self);
size_t queue_get_count(queue_t * self);
void queue_print(queue_t * self);
void queue_delete(queue_t * self);

