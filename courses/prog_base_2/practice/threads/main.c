#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "thread.h"
#include "mutex.h"
struct settings{
    mutex_t * m;
    int * color;
    int startpos;
};
void __sleep(int ms) {
#ifdef _WIN32
    Sleep(ms*3);
#elif defined __linux__
    usleep(ms * 1000);
#endif // _WIN32
}
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void * jump_letter(void * args)
{
    struct settings * set = args;
    char c = '#';
    int color = 0;
    int pos = set->startpos;
    while(1)
    {
        mutex_lock(set->m);
        color = *(set->color);
        mutex_unlock(set->m);
        if(color > 255 || color < 0)
            color = 0;
        for(int i = 0; i < 5; i++)
        {

            setCursorPosition(i,pos);
            setConsoleColor(color);
            putchar(c);
            __sleep(100);
            setCursorPosition(i, pos);
            putchar(' ');
        }
        mutex_unlock(set->m);
        __sleep(300);
    }
}

void * get_color(void * args)
{
    struct settings * set = args;
    while(1)
    {
        char c = getch();
        mutex_lock(set->m);
        *(set->color)= c;
        mutex_unlock(set->m);
        rewind(stdin);
    }
}
int main(void)
{
    mutex_t * mu = mutex_new();
    int color;
    struct settings set = {mu, &color, 0};
    struct settings set1 = {mu, &color, 1};
    thread_t * getcolor = thread_create_args(get_color, &set);
    thread_t * jumpletter = thread_create_args(jump_letter, &set);
    __sleep(100);
    thread_t * jumpletter1 = thread_create_args(jump_letter, &set1);
    Sleep(10000000);
    mutex_free(mu);
    thread_free(getcolor);
    thread_free(jumpletter);
    return EXIT_SUCCESS;
}
