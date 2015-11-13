#include <windows.h>
#include <stdlib.h>
#define RED BACKGROUND_RED
#define PURPLE BACKGROUND_RED | BACKGROUND_BLUE
#define YELLOW BACKGROUND_RED | BACKGROUND_GREEN
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void setConsoleColor(int curColorPos)
{
    int color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(curColorPos==2)
        color = RED | BACKGROUND_INTENSITY;
    else if(curColorPos==1)
        color = PURPLE | BACKGROUND_INTENSITY;
    else if(curColorPos==0)
        color = YELLOW | BACKGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, color);
}
void consoleFill(int rows, int columns)
{
    int i, curRow;
    for(i = 0, curRow = 0; curRow<rows; i++, curRow = (i/columns))
    {
        int left = curRow %2 ? 0 : 1;
        int curColumn = left ? (columns-1)-i%columns : i%columns;
        int curColorPos = abs( (curColumn - curRow) % 3);
        if(curRow > curColumn)
            curColorPos = 2 - abs( (curColumn - curRow - 2) % 3);
        setCursorPosition(curColumn, curRow);
        setConsoleColor(curColorPos);
        printf("*"); /* " " is more beautiful */
        Sleep(1);
    }
    setCursorPosition(0, 0);
}
int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleFill(rows, columns);
    getchar();
}
