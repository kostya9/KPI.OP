#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#elif defined __linux__
    #include <unistd.h>
#endif // _WIN32

#include "thread.h"
#include "mutex.h"

void __sleep(int ms);

static mutex_t * mu;

void * run1(void * args) {
    mutex_lock(mu);
    for(int i = 0; i < 100; i++) {
        if(i > 10) {
            mutex_unlock(mu);
            thread_exit("EXITED");
        }
        printf(" %s %i\n", (const char *)args, i);
        __sleep(30);
    }
    return args;
}

void * run2(void * args) {
    mutex_lock(mu);
    for(int i = 0; i < 50; i++) {
        printf(" %s \n", (const char *)args);
        __sleep(60);
    }
    mutex_unlock(mu); // warning for thread_terminate!
    return args;
}

int main(void) {
    mu = mutex_new();
    thread_t * t1 = thread_create_args(run1, "Hello");
    __sleep(100);
    thread_t * t2 = thread_create_args(run2, "World");
    __sleep(1000);
    void * res1 = NULL;
    thread_join_result(t1, &res1);
    printf("\nThread 1 res: <<<%s>>>\n", (const char *)(res1));
    //thread_terminate(t2);
    __sleep(1000);
    thread_join_result(t2, &res1);
    printf("\nThread 2 res: <<<%s>>>\n", (const char *)(res1));
    return 0;
}

void __sleep(int ms) {
#ifdef _WIN32
    Sleep(ms*3);
#elif defined __linux__
    usleep(ms * 1000);
#endif // _WIN32
}
