#include "user.h"
#include "event.h"
#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include "stack_test.h"
#define arr_len(a) sizeof(a)/sizeof(a[0])

void normal_alert (user_t * receiver, event_t * event);
void strange_alert (user_t * receiver, event_t * event);
void runTests();

int main(void)
{
    puts("Running unit tests for module stack");
    runTests();
    puts("Press anything to proceed to testing events...\n");
    getch();

    user_t * user_daniil = user_new("Daniil");
    user_t * user_vasya = user_new("Vasya");
    user_t * user_natasha = user_new("Natasha");
    user_t * user_katya = user_new("Katya");
    user_t * user_petya = user_new("Petya");
    user_t * user_sasha = user_new("Sasha");

    unsigned int seconds = 10;
    event_t * event = event_new(time(NULL) + seconds, "THIS IS A SUPER DUPER EVENT YEEE");
    event_add_alert(event, user_daniil, normal_alert);
    event_add_alert(event, user_vasya, normal_alert);
    event_add_alert(event, user_natasha, strange_alert);
    printf("Event 1 going on in %i seconds. Waiting...\n", seconds);

    unsigned int seconds_two = 12;
    printf("Setting up event 2 (group) which will be in %i seconds. Waiting ...\n ", seconds_two);
    event_t * event_two = event_new(time(NULL) + seconds_two, "THIS IS A SUPER DUPER EVENT TWO");
    user_t * users[6] = {user_daniil, user_vasya, user_natasha, user_katya, user_petya, user_sasha};
    event_add_alert_group(event_two, users, arr_len(users), normal_alert);

    Sleep(20 * 1000);

    event_delete(event);
    event_delete(event_two);

    for(unsigned int i = 0; i < arr_len(users); i++)
        user_delete(users[i]);

    return EXIT_SUCCESS;
}

void runTests()
{
    stack_test();
}

void normal_alert (user_t * receiver, event_t * event)
{
    char * name = user_get_name(receiver);
    char * summary = event_get_summary(event);

    printf("\nHey, %s\n", name);
    printf("Notifying you that event has started. It's summary : \n%s\n", summary);

    free(name);
    free(summary);
}

void strange_alert (user_t * receiver, event_t * event)
{
    char * name = user_get_name(receiver);
    char * summary = event_get_summary(event);

    printf("\nHEYYY NERD, IS UR NAME %s ? THEN UR PARTY HAS STARTED. LETSS GOOO!\n", name);
    printf("Actually it's summary is:\n%s\n", summary);

    free(name);
    free(summary);
}

