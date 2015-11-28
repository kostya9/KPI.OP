#ifndef __snake_
#define __snake_
#include <windows.h>
#define COLORDEF 0x07
#define COLORAPPLE  BACKGROUND_RED
#define COLORSNAKE  BACKGROUND_GREEN
#define APPLECOUNT 15
#define MAXLENGTH 160
enum direction {RIGHT = -4, LEFT, UP, DOWN};
typedef struct {
        int length;
        enum direction dir;
        POINT * body;} Snake;
typedef struct
{
    int x;
    int y;
}Apple;
void CheckApple(Snake * s, Apple apples[], int * apple);
void DeleteSnake(Snake * s);
int DrawSnake(Snake * s, int level);
int RefreshSnake(Snake * s, Apple apples[], int level);
void ChangeDirection(Snake * s, char c);
int checkCollide(Snake * s);
int initSnake(int level);
#endif // __snake_
