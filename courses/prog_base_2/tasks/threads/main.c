#include <stdio.h>
#include <windows.h>
#include "printer.h"
#include "libthread/mutex.h"
int main()
{
    mutex_t * mutex = mutex_new();
    printer_t * printer = printer_new("Hi Folks", mutex);
    printer_t * printer1 = printer_new("Hi Non Folks", mutex);
    printer_t * printer2 = printer_new("Hi Non Folks And Folks", mutex);

    printer_start(printer);
    printer_start(printer1);
    printer_start(printer2);
    Sleep(20);

    printer_stop(printer);
    printer_stop(printer1);
    printer_stop(printer2);

    printer_free(printer);
    printer_free(printer1);
    printer_free(printer2);
    mutex_free(mutex);

    return EXIT_SUCCESS;
}
