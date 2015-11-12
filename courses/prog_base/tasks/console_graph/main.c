/*
W A S D - type control
+-    -  scaling */
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void initFunction(int rows, int columns, int xCenter, int yCenter, int scale)
{
    setCursorPosition(0, 0);
    puts("F(x) = cos(x^2) + sin(2 * x)^2 + 1");
    puts("F(x) = x^1.5 + 2 * x - 3;");
    int i, j;
    float prevF= 10;
    setConsoleColor(BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    for(i = xCenter; i < columns; i++)
    {
        float k = (float)(i - xCenter)/scale;
        float func = scale * (cos(pow(k, 2)) + pow(sin(2 * k), 2) + 1);
        if(yCenter - func >= 0)
        {
            setCursorPosition(i,yCenter - func);
            printf(" ");
        }
        while(prevF!=10 && k!=0 && abs((int)prevF - (int)func)>=1)
        {
            int temp = i;
            if(prevF < func)
            {
                prevF++;
            }
            else if(prevF > func)
            {
                prevF--;
                temp--;
            }
            setCursorPosition(temp,yCenter - prevF);
            if(yCenter - prevF >= 0 && abs((int)prevF - (int)func)>=1)
                printf(" ");
        }
        prevF = func;
    }
    for(i = xCenter; i >= 0; i--)
    {
        float k = (float)(i - xCenter)/scale;
        float func = scale * (cos(pow(k, 2)) + pow(sin(2 * k), 2) + 1);
        if(yCenter - func >= 0)
        {
            setCursorPosition(i,yCenter - func);
            printf(" ");
        }
        while(prevF!=10 && k!=0 && abs((int)prevF - (int)func)>=1)
        {
            int temp = i;
            if(prevF < func)
            {
                prevF++;
            }
            else if(prevF > func)
            {
                prevF--;
                temp--;
            }
            setCursorPosition(temp,yCenter - prevF);
            if(yCenter - prevF >= 0 && abs((int)prevF - (int)func)>=1)
                printf(" ");
        }
        prevF = func;
    }
    setConsoleColor(0xF0);
}
void initFunction1(int rows, int columns, int xCenter, int yCenter, int scale)
{
    int i, j;
    float prevF= 10;
    setConsoleColor(0x5|BACKGROUND_INTENSITY);
    for(i = xCenter; i < columns; i++)
    {
        float k = (float)(i - xCenter)/scale;
        float func = scale * (pow(k, 1.5) + 2 * k - 3);
        if(yCenter - func >= 0 && yCenter - func < rows)
        {
            setCursorPosition(i,yCenter - func);
            printf(" ");
        }
        while(prevF!=10 && k!=0 && abs((int)prevF - (int)func)>=1)
        {
            int temp = i;
            if(prevF < func)
            {
                prevF++;
            }
            else if(prevF > func)
            {
                prevF--;
                temp--;
            }
            setCursorPosition(temp,yCenter - prevF);
            if(yCenter - prevF >= 0 && abs((int)prevF - (int)func)>=1 && yCenter - prevF < rows)
                printf(" ");
        }
        prevF = func;
    }
    for(i = xCenter; i >= 0; i--)
    {
        float k = (float)(i - xCenter)/scale;
        float func = scale * (pow(k, 1.5) + 2 * k - 3);
        if(yCenter - func >= 0&& yCenter - func < rows)
        {
            setCursorPosition(i,yCenter - func);
            printf(" ");
        }
        while(prevF!=10 && k!=0 && abs((int)prevF - (int)func)>=1)
        {
            int temp = i;
            if(prevF < func)
            {
                prevF++;
            }
            else if(prevF > func)
            {
                prevF--;
                temp--;
            }
            else
                break;
            setCursorPosition(temp,yCenter - prevF);
            if(yCenter - prevF >= 0 && abs((int)prevF - (int)func)>=1 && yCenter - prevF < rows)
                printf(" ");
        }
        prevF = func;
    }
    setConsoleColor(0xF0);
}
void initDecart(int rows, int columns, int xCenter, int yCenter, int scale)
{
    int i, j, k;
    for(i = xCenter; i < columns; i+=scale)
    {
        setCursorPosition(i, yCenter);
        printf(".");
    }
    setCursorPosition(i - scale - 2, yCenter + 1);
    printf(" X ");
    for(i = xCenter; i >= 0; i-=scale)
    {
        setCursorPosition(i, yCenter);
        printf(".");
    }
    for(i = yCenter; i >= 0; i-=scale)
    {
        setCursorPosition(xCenter, i);
        printf(".");
    }
    setCursorPosition(xCenter + 3, i  - scale);
    printf(" Y ");
    for(i = yCenter; i < rows; i+=scale)
    {
        setCursorPosition(xCenter, i);
        printf(".");
    }
}
void initConsole(int xCenter, int yCenter, int scale)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    if(scale<=0)
        scale = 2;
    if(xCenter < 0 || xCenter > columns)
        xCenter = columns/2;
    if(yCenter < 0 || yCenter > rows)
        yCenter = rows/2;
    initDecart(rows, columns, xCenter, yCenter, scale);
    initFunction(rows, columns, xCenter, yCenter, scale);
    initFunction1(rows, columns, xCenter, yCenter, scale);
    getKey(xCenter, yCenter, scale);
}
void getKey(int xCenter, int yCenter, int scale)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    char c = getch();
    switch(c)
    {
        case 'w':
        {
            system("cls");
            initConsole(xCenter, --yCenter, scale);
        }break;
        case 'a':
        {
            system("cls");
            initConsole(--xCenter, yCenter, scale);
        }break;
        case 'd':
        {
            system("cls");
            initConsole(++xCenter, yCenter, scale);
        }break;
        case 's':
        {
            system("cls");
            initConsole(xCenter, ++yCenter, scale);
        }break;
        case '-':
        {
            system("cls");
            initConsole(xCenter, yCenter, --scale);
        }break;
        case '+':
        {
            system("cls");
            initConsole(xCenter, yCenter, ++scale);
        }break;
    }
}
int main(void)
{
    initConsole(-1, -1, -1);
    return EXIT_SUCCESS;
}

