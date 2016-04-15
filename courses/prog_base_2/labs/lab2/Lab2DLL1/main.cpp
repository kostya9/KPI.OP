#include "main.h"

// a sample exported function
#include "queue.h"
int DLL_EXPORT condition(queue_t * queue)
{
    int deq;
    int count = queue_get_count(queue);
    for(int i = 0; i < count; i++)
    {
        deq = queue_dequeue(queue);
        queue_enqueue(queue, deq);
    }
    return deq < 0;
}
void DLL_EXPORT modify(queue_t * queue)
{
    int el = queue_dequeue(queue);
    while(!queue_is_empty(queue))
    {
        el = queue_dequeue(queue);
    }
    queue_enqueue(queue, el);
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
