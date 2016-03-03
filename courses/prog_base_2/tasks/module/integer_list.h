#pragma once
#include <stdlib.h>

#define RETURN_FAILURE 1
#define RETURN_SUCCESS 0

typedef struct integer_list_s* integer_list_t;

integer_list_t integer_list_create();
integer_list_t integer_list_create_arr(int arr[], size_t size);
void integer_list_remove(integer_list_t list);


int integer_list_insert(integer_list_t list, int index, int data)
int integer_list_delete();
int integer_list_get_size();
int integer_list_get_count_negative();
int integer_list_get_count_zero();
int integer_list_get_count_positive();
