#include <stdio.h>
#include <windows.h>
#include "printer.h"
int main()
{
    printer_t * printer = printer_new("Hi Folks");
    printer_t * printer1 = printer_new("Hi Non Folks");
    printer_t * printer2 = printer_new("Hi Non Folks And Folks");

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

    return EXIT_SUCCESS;
}
