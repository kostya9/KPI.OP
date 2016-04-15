#include "main.h"
#include "queue.h"
#include <stdio.h>
// a sample exported function
int get_sum(queue_t * queue)
{
    int sum = 0;
    for(size_t i = 0; i < queue_get_count(queue); i++)
    {
        int el = queue_dequeue(queue);
        sum+=el;
        queue_enqueue(queue, el);
    }
    return sum;
}
int DLL_EXPORT condition(queue_t * queue)
{
    int sum = get_sum(queue);
    return sum > 100;
}
void DLL_EXPORT modify(queue_t * queue)
{
    int sum = get_sum(queue);
    while(sum >= 50)
    {
        int el = queue_dequeue(queue);
        sum -= el;
        if(el > 0)
            el = - el;
        queue_enqueue(queue, el);
        sum+= el;
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
