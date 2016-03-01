#pragma once

#define MIN_CAPACITY 2

typedef struct int_list_s* int_list_t;

int_list_t int_list_new();
void int_list_delete(int_list_t list);

void int_list_insert(int_list_t list, int element, int index);
void int_list_remove(int_list_t list, int index);

int int_list_get_element(int_list_t list, int index);
int int_list_get_size(int_list_t list);
int int_list_get_negcount(int_list_t list);
int int_list_get_poscount(int_list_t list);
int int_list_get_zerocount(int_list_t list);
