#include <limits.h>
#include "queue.h"
#include "dynamic.h"
#include <stdio.h>
#define BUFFER_SIZE 1024
#define arr_len(a) sizeof(a)/sizeof(a[0])
dynamic_t * loadDLL();
int main(void)
{
    char buffer[BUFFER_SIZE];
    queue_t * queue = queue_new();
    dynamic_t * dyn = loadDLL();
    while(1)
    {
        puts("Printing out the queue...");
        queue_print(queue);
        int number;
        puts("Print out the next number");
        fgets(buffer, arr_len(buffer), stdin);
        int status = sscanf(buffer, "%i\n", &number);
        queue_enqueue(queue, number);
        if(dyn->condition(queue))
        {
            puts("Condition met, modifying...");
            dyn->modify(queue);
        }


    }
    dynamic_clean(dyn);
    return EXIT_SUCCESS;
}
dynamic_t * loadDLL()
{
    char buffer[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    puts("Type in 1 or 2 for loading first or second DLL");
    fgets(buffer, BUFFER_SIZE, stdin);
    if(buffer[0] == '1')
        strcpy(name, "Lab2DLL1.dll");
    else if(buffer[0] == '2')
        strcpy(name, "Lab2DLL2.dll");
    dynamic_t * dyn = dynamic_init(name);
    return dyn;
}
