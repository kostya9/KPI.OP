#pragma once

#include "user.h"
#include <time.h>
#include <stdlib.h>

typedef struct event_s event_t;
typedef void(*alert_fn)(user_t * receiver, event_t * event);

typedef enum EVENT_STATUS{EVENT_FULL, EVENT_OK} EVENT_STATUS;

event_t * event_new(time_t time_event, char * summary);
void event_delete(event_t * event);

/*Returns pointer to dynamically allocated memory with summary*/
char * event_get_summary(event_t * self);

EVENT_STATUS event_add_alert(event_t * self, user_t * user, alert_fn fn);
size_t event_add_alert_group(event_t * self, user_t ** users, size_t users_count, alert_fn fn);
