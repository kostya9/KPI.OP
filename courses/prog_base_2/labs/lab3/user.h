#pragma once

typedef struct user_s user_t;

user_t * user_new(const char * name);
/*Returns dynamically allocated memory*/
char * user_get_name(user_t * user);
void user_delete(user_t * self);
