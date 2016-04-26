#include "event.h"

#include "libthread\mutex.h"
#include "libthread\thread.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#define BUFFER_LEN 1024

static void * check_func(void * args);

struct alert_s{
    user_t * receiver;
    alert_fn fn;
};

struct event_s{
    //mutex_t * mutex;
    thread_t * thread;
    char summary[BUFFER_LEN];
    time_t time;
    stack_t * alert_list; // list of alerts
};


event_t * event_new(time_t time_event, char * summary)
{
    if((int)time_event < (int)time(NULL))
        return NULL; // This has already happened

    event_t * self = malloc(sizeof(event_t));

    strcpy(self->summary, summary);
    self->time = time_event;
    self->alert_list = stack_new(5); // 5 max
    self->thread = thread_create_args(check_func, self);
    return self;
}

static void * check_func(void * args)
{
    event_t * self = (event_t *)args;
    while(1)
    {
        if(self->time < time(NULL))
        {
            stack_t * alert_list = self->alert_list;
            int list_count = stack_get_count(alert_list);
            for(unsigned int i = 0; i < list_count; i++)
            {
                struct alert_s * alert = (struct alert_s *)stack_pop(alert_list);
                alert->fn(alert->receiver, self);
            }
            break;
        }
    }
    return NULL;
}

void event_delete(event_t * self)
{
    thread_terminate(self->thread);
    thread_free(self->thread);
    int list_count = stack_get_count(self->alert_list);
    for(unsigned int i = 0; i < list_count; i++)
    {
        free(stack_pop(self->alert_list));
    }
    stack_delete(self->alert_list);
    free(self);
}

char * event_get_summary(event_t * self)
{
    char * summary = malloc((strlen(self->summary) + 1) * sizeof(char));
    strcpy(summary, self->summary);
    return summary;
}

EVENT_STATUS event_add_alert(event_t * self, user_t * user, alert_fn fn)
{
    struct alert_s * alert = malloc(sizeof(struct alert_s));
    alert->fn = fn;
    alert->receiver = user;
    int rc = stack_push(self->alert_list, alert);
    if(rc == STACK_ERROR)
        return EVENT_FULL;
    return EVENT_OK;
}

size_t event_add_alert_group(event_t * self, user_t ** users, size_t users_count, alert_fn fn)
{
    size_t actually_added = 0;
    for(unsigned int i = 0; i < users_count; i++)
    {
        if(event_add_alert(self, users[i], fn) == EVENT_OK)
            actually_added++;
        else
            puts("\nCannot add a user. The event notification list is full.");
    }
    return actually_added;
}
