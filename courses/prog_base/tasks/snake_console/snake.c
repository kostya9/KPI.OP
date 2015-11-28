#include <conio.h>
#include "snake.h"
#include "console.h"
int initSnake(int level)
{
    int columns, rows, i;
    setFontSize(SNAKEFONT, SNAKEFONT);
    getConsoleAttributes(&rows, &columns);
    setConsoleColor(COLORDEF);
    system("cls");
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
    s.body = body;
    s.body[0].x = 0;
    s.body[0].y = 0;
    s.length = 1;
    s.dir = RIGHT;
    RefreshSnake(&s, apples, level);
    return s.length - 1;
}
void DeleteSnake(Snake * s)
{
    int i;
    setConsoleColor(COLORDEF);
    setCursorPosition(s->body[s->length - 1].x, s->body[s->length - 1].y);
    printf(" ");
}
int DrawSnake(Snake * s, int level)
{
    int i = 0;
    int rows, columns;
    getConsoleAttributes(&rows, &columns);
    setConsoleColor(COLORSNAKE);
    for(i = s->length - 1; i > 0; i--)
    {
        s->body[i].x = s->body[i-1].x;
        s->body[i].y = s->body[i-1].y;
    }
    switch(s->dir)
    {
        case RIGHT:
        {
            if(s->body[0].x != columns - 1)
                (s->body[0].x)++;
            else
                return 1;
        }break;
        case LEFT:
        {
            if(s->body[0].x != 0)
                (s->body[0].x)--;
            else
                return 1;
        }break;
        case UP:
        {
            if(s->body[0].y != 0)
                (s->body[0].y)--;
            else
                return 1;
        }break;
        case DOWN:
        {
            if(s->body[0].y != rows - 1)
                (s->body[0].y)++;
            else
                return 1;
        }break;
    }
    setCursorPosition(s->body[0].x, s->body[0].y);
    printf(" ");
    setConsoleColor(COLORDEF);
    Sleep(150 - level * 10);
    return 0;
}
void ChangeDirection(Snake * s, char c)
{
    switch(c)
    {
        case 'w': case 'W':
            if(s->length==1 || s->dir!=DOWN)
                s->dir = UP;
        break;
        case 's': case 'S':
            if(s->length==1 || s->dir!=UP)
                s->dir = DOWN;
        break;
        case 'a': case 'A':
            if(s->length==1 || s->dir!=RIGHT)
                s->dir = LEFT;
        break;
        case 'd': case 'D':
            if(s->length==1 || s->dir!=LEFT)
                s->dir = RIGHT;
        break;
    }
}
void CheckApple(Snake * s, Apple apples[], int * level)
{
    int i;
    for(i = 0; i < APPLECOUNT; i++)
        if(s->body[0].x==apples[i].x && s->body[0].y==apples[i].y)
        {
            int rows, columns;
            getConsoleAttributes(&rows, &columns);
            apples[i].x = rand()%columns;
            apples[i].y = rand()%rows;
            setCursorPosition(apples[i].x, apples[i].y);
            setConsoleColor(COLORAPPLE);
            printf(" ");
            s->length++;
            if(s->length % 3 == 1 && (*level) <9)
                (*level)++;
            break;
        }
}
int checkCollide(Snake * s)
{
    int i, j;
    for(i = 0; i < s->length; i++)
        for(j = 0; j < s->length; j++)
            if(i!=j && s->body[i].x == s->body[j].x && s->body[i].y == s->body[j].y)
                return 1;
    return 0;

}
int RefreshSnake(Snake * s, Apple apples[], int level)
{
    DeleteSnake(s);
    char c;
    if(kbhit())
    {
        c = getch();
        ChangeDirection(s, c);
    }
    CheckApple(s, apples, &level);
    if(DrawSnake(s, level) || checkCollide(s))
        return 1;
    RefreshSnake(s, apples, level);
    return 0;
}
