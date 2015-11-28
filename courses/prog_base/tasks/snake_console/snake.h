#ifndef __snake_
#define __snake_
#include <windows.h>
#define COLORDEF 0x07
#define COLORAPPLE  BACKGROUND_RED
#define COLORSNAKE  BACKGROUND_GREEN
#define APPLECOUNT 5
#define MAXLENGTH 160
enum direction {RIGHT = -4, LEFT, UP, DOWN};
typedef struct {
        POINT head;
        int length;
        enum direction dir;
        POINT * body;} Snake;
typedef struct
{
    int x;
    int y;
}Apple;
void CheckApple(Snake * s, Apple apples[]);
void DeleteSnake(Snake * s);
void DrawSnake(Snake * s);
void RefreshSnake(Snake * s, Apple apples[]);
void ChangeDirection(Snake * s, char c);
#endif // __snake_
