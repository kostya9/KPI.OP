#pragma once
#include "libthread/mutex.h"
typedef struct printer_s printer_t;

printer_t * printer_new(const char * str, mutex_t * mutex);
void printer_set_string(printer_t * printer, const char * str);
void printer_start(printer_t * printer);
void printer_stop(printer_t * printer);
void printer_free(printer_t * printer);


