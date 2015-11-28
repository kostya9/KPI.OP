#include "snake.h"
#include "console.h"
void DeleteSnake(Snake * s)
{
    int i;
    setConsoleColor(COLORDEF);
    if(s->length==0)
        setCursorPosition(s->head.x, s->head.y);
    else
        setCursorPosition(s->body[0].x, s->body[0].y);
    printf(" ");
}
void DrawSnake(Snake * s)
{
    int i = 0;
    int rows, columns;
    getConsoleAttributes(&rows, &columns);
    setConsoleColor(COLORSNAKE);
    if(s->length > 0)
    {
        for(i = 0; i < s->length - 2; i++) /*New snake block is the last but not like tha array - redo that the last snake thing is the last IN THE ARRAY*/
        {
            s->body[i].x = s->body[i+1].x;
            s->body[i].y = s->body[i+1].y;
            setCursorPosition(s->body[i].x, s->body[i].y);
            printf(" ");
        }
        s->body[i].x = s->head.x;
        s->body[i].y = s->head.y;
        setCursorPosition(s->body[i].x, s->body[i].y);
        printf(" ");
    }
    switch(s->dir)
    {
        case RIGHT:
        {
            if(s->head.x != columns - 1)
                (s->head.x)++;
            else
                return;
        }break;
        case LEFT:
        {
            if(s->head.x != 0)
                (s->head.x)--;
            else
                return;
        }break;
        case UP:
        {
            if(s->head.y != 0)
                (s->head.y)--;
            else
                return;
        }break;
        case DOWN:
        {
            if(s->head.y != rows - 1)
                (s->head.y)++;
            else
                return;
        }break;
    }
    setCursorPosition(s->head.x, s->head.y);
    printf(" ");
    setConsoleColor(COLORDEF);
    Sleep(100);
}
void ChangeDirection(Snake * s, char c)
{
    switch(c)
    {
        case 'w': case 'W':
            s->dir = UP;
        break;
        case 's': case 'S':
            s->dir = DOWN;
        break;
        case 'a': case 'A':
            s->dir = LEFT;
        break;
        case 'd': case 'D':
            s->dir = RIGHT;
        break;
    }
}
void CheckApple(Snake * s, Apple apples[])
{
    int i;
    for(i = 0; i < APPLECOUNT; i++)
        if(s->head.x==apples[i].x && s->head.y==apples[i].y)
        {
            int rows, columns;
            getConsoleAttributes(&rows, &columns);
            apples[i].x = rand()%columns;
            apples[i].y = rand()%rows;
            setCursorPosition(apples[i].x, apples[i].y);
            setConsoleColor(COLORAPPLE);
            printf(" ");
            s->length++;
            break;
        }
}
void RefreshSnake(Snake * s, Apple apples[])
{
    DeleteSnake(s);
    char c;
    if(kbhit())
    {
        c = getch();
        ChangeDirection(s, c);
    }
    CheckApple(s, apples);
    DrawSnake(s);
    RefreshSnake(s, apples);
}
