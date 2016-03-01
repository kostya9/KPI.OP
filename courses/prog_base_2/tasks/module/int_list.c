#include <stdlib.h>
#include "int_list.h"

struct int_list_s
{
    int * array;
    int size;
    int capacity;
};

int_list_t int_list_new()
{
    int * array = (int *)malloc(MIN_CAPACITY * sizeof(int));
    int_list_t newstruct = (struct int_list_s*)malloc(sizeof(struct int_list_s));
    newstruct->array = array;
    newstruct->size = 0;
    newstruct->capacity = MIN_CAPACITY;
    return newstruct;
}

void int_list_delete(int_list_t list)
{
    free(list->array);
    free(list);
}

static void increase_capacity(int_list_t list)
{
    int new_capacity = 2 * list->capacity;
    int * new_array = (int *)realloc(list->array, new_capacity * sizeof(int));
    list->array = new_array;
    list->capacity = new_capacity;
}
static void shiftright(int_list_t list, int starting_index)
{
    if(list->size >= list->capacity)
        increase_capacity(list); // ERROR
    int end = list->size;
    for(int i = starting_index, temp = list->array[i]; i < end; i++)
    {
        int prevtemp = list->array[i + 1];
        list->array[i + 1] = temp;
        temp = prevtemp;
    }
}
static void shiftleft(int_list_t list, int starting_index)
{
    int end = list->size - 1;
    for(int i = starting_index; i < end; i++)
        list->array[i] = list->array[i + 1];
}


//moves the value next
void int_list_insert(int_list_t list, int element, int index)
{
    if(index > list->size)
        return; // ERROR
    shiftright(list, index);
    list->array[index] = element;
    list->size++;
}

void int_list_remove(int_list_t list, int index)
{
    if(index < 0 || index >= list->size)
        return; // ERROR
    shiftleft(list, index);
    list->size--;
}

int int_list_get_size(int_list_t list)
{
    return list->size;
}

int int_list_get_negcount(int_list_t list)
{
    int count = 0;
    int size = list->size;
    for(int i = 0; i < size; i++)
        if(list->array[i] < 0)
            count++;
    return count;
}
int int_list_get_poscount(int_list_t list)
{
    int count = 0;
    int size = list->size;
    for(int i = 0; i < size; i++)
        if(list->array[i] > 0)
            count++;
    return count;
}

int int_list_get_zerocount(int_list_t list)
{
    int count = 0;
    int size = list->size;
    for(int i = 0; i < size; i++)
        if(list->array[i] == 0)
            count++;
    return count;
}

int int_list_get_element(int_list_t list, int index)
{
    if(index >= list->size)
        return;
    return list->array[index];
}
