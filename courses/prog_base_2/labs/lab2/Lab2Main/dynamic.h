#pragma once
#include "queue.h"
#include <windows.h>
typedef int (*cond_f)(queue_t * queue);
typedef void (*modif_f)(queue_t * a);

typedef struct dynamic_s {
    HANDLE hLib;
    cond_f condition;
    modif_f modify;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);
