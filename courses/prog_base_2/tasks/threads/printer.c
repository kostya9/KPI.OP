#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "printer.h"
#include "libthread/mutex.h"
#include "libthread/thread.h"
#define TIMES 10
static mutex_t* mutex;

typedef struct printer_s
{
    int is_active;
    char * str;
    thread_t * thread;
} printer_s;

printer_t * printer_new(const char * str)
{
    if(mutex == NULL)
        mutex = mutex_new();
    printer_s * printer = malloc(sizeof(struct printer_s));
    printer->str = (char *)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(printer->str, str);
    return printer;
}
static void * printer_print(void * args)
{
    printer_t * printer = (printer_t *)args;
    while(printer->is_active)
    {
        mutex_lock(mutex);
        for(int i = 0; i < TIMES; i++)
        {
            puts(printer->str);
        }
        mutex_unlock(mutex);
    }
}
void printer_set_string(printer_t * printer, const char * str)
{
    if(printer->is_active == 0)
        strcpy(printer->str, str);
}
void printer_start(printer_t * printer)
{
    if(printer->is_active == 1)
        return;
    printer->is_active = 1;
    printer->thread = thread_create_args(printer_print, printer);
}
void printer_stop(printer_t * printer)
{
    if(printer->is_active == 0)
        return;
    printer->is_active = 0;
    thread_free(printer->thread);
}
void printer_free(printer_t * printer)
{
    if(printer->is_active)
    {
        printer->is_active = 0;
        thread_free(printer->thread);
    }
    free(printer->str);
    free(printer);
}
