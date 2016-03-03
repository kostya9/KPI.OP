#include "integer_list.h"
#include <stdlib.h>

//Linked List
typedef struct integer_node_s
{
    int data;
    struct integer_node_s * next;
} integer_node;
typedef struct integer_list_s
{
    integer_node * head;
} integer_list_s;

integer_node * get_node(integer_list_t list, int index);

integer_list_t integer_list_create_arr(int arr[], size_t size) // Could be zero?
{
    integer_list_t new_list = malloc(sizeof(integer_list_s));
    integer_node * cur_node;

    if(size == 0)
        return integer_list_create();

    for(int i = 0; i < size; i++)
    {
        if(i == 0)
        {
            new_list->head = malloc(sizeof(integer_node));
            new_list->head->data = arr[i];
            cur_node = new_list->head;
        }
        else
        {
            cur_node->next = malloc(sizeof(integer_node));
            cur_node->next->data = arr[i];
            cur_node = cur_node->next;
        }
    }
    return new_list;
}

integer_list_t integer_list_create()
{
    integer_list_t new_list = malloc(sizeof(integer_list_s));
    return new_list;
}

void integer_list_remove(integer_list_t list)
{
    if(list->head == NULL)
    {
        free(list);
        return;
    }

    integer_node* prev_node = list->head;
    while(prev_node != NULL)
    {
        integer_node* next_node = prev_node->next;
        free(prev_node);
        prev_node = next_node;
    }
    free(list);
    return;
}

integer_node * get_node(integer_list_t list, int index)
{
    integer_node * cur_node = list->head;
    for(int i = 1; i < index; i++)
    {
        if(cur_node == NULL)
            return NULL;
        cur_node = cur_node->next;
    }
    return cur_node;
}

int integer_list_insert(integer_list_t list, int index, int data)
{
    if(index < 0)
        return RETURN_FAILURE;

    if(index >= integer_list_get_size())
        return RETURN_FAILURE;

    integer_node * new_node = malloc(sizeof(integer_node));
    new_node->data = data;

    integer_node * prev_node = get_node(list, index - 1);
    integer_node * next_node = get_node(list, index + 1);
    if(prev_node != NULL)
        prev_node->next = new_node;
    else
        list->head = new_node;

    if(next_node != NULL)
        new_node->next = next_node;

    return RETURN_SUCCESS;
}
