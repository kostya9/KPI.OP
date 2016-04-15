#include "dynamic.h"
#include <stdlib.h>
#include <windows.h>
dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->condition = NULL;
    dyn->modify = NULL;
    if (NULL != dyn->hLib) {
        dyn->condition = (cond_f)GetProcAddress(dyn->hLib, "condition");
        dyn->modify = (modif_f)GetProcAddress(dyn->hLib, "modify");
        return dyn;
    } else {
        return NULL;
    }
}
void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
