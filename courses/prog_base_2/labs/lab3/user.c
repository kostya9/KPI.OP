#include "user.h"
#include <malloc.h>
#include <string.h>
#define BUFFER_LEN 1024
struct user_s {
    char name[BUFFER_LEN];
};

user_t * user_new(const char * name)
{
    user_t * self = malloc(sizeof(user_t));
    strcpy(self->name, name);
    return self;
}

char * user_get_name(user_t * self)
{
    char * name = malloc((strlen(self->name) + 1) * sizeof(char));
    strcpy(name, self->name);
    return name;
}

void user_delete(user_t * self)
{
    free(self);
}

