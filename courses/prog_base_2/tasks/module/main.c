#include "int_list.h"

int main(void)
{
    const int size = 10;
    int_list_t list = int_list_new();
    for(int i = 0; i < size; i++)
    {
        int_list_insert(list, i - 5, 0);
    }
    output(list);
    int_list_remove(list, 3);
    puts("Removed the 3rd element : ");
    output(list);
    printf("There are \n|| %i negatives \n|| %i positives\n|| %i 0s", int_list_get_negcount(list), int_list_get_poscount(list), int_list_get_zerocount(list));
    int_list_delete(list);
}
void output(int_list_t list)
{
    const int size = int_list_get_size(list);
    puts("List : ");
    printf("[ ");
    for(int i = 0; i < size; i++)
    {
        printf("%2i ", int_list_get_element(list, i));
    }
    puts(" ]");
}
