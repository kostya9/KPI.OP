#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"
int main(void)
{
    int columns, rows, i;
    getConsoleAttributes(&rows, &columns);
    Apple apples[APPLECOUNT];
    POINT body[MAXLENGTH];
    for(i = 0; i < APPLECOUNT; i++)
    {
        apples[i].x = rand()%columns;
        apples[i].y = rand()%rows;
        setCursorPosition(apples[i].x, apples[i].y);
        setConsoleColor(COLORAPPLE);
        printf(" ");
    }
    Snake s;
    s.head.x = 0;
    s.head.y = 0;
    s.body = body;
    s.length = 0;
    s.dir = RIGHT;
    RefreshSnake(&s, apples);
}
