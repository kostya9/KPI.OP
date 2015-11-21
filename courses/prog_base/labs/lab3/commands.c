#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "commands.h"
#include "arrFuncs.h"
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void clearZone(int xFrom, int yFrom, int xTo, int yTo, int color)
{
    int i, j;
    setConsoleColor(color);
    for(i = xFrom; i <= xTo; i++)
        for(j = yFrom; j <= yTo; j++)
        {
            setCursorPosition(i, j);
            printf(" ");
        }
    setConsoleColor(COLORDEF);
}

void printArrEl(double arr[], size_t size, int el)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    setConsoleColor(COLORWORKFOR);
    clearZone(RIGHTBORDER, el + 1, LENGTH - 1, el + 1, COLORSELECT);
    setConsoleColor(COLORSELECT);
    setCursorPosition(RIGHTBORDER + (LENGTH - (RIGHTBORDER))/3 - 3 , el + 1);
    printf("%.2f", arr[el]);
    setCursorPosition(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y);
    setConsoleColor(COLORDEF);
}
void printArr(double arr[], size_t size)
{
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    int i;
    clearZone(RIGHTBORDER, 1, LENGTH - 1, size, COLORWORKFOR);
    setConsoleColor(COLORWORKFOR);
    for(i = 0; i < size; i++)
    {
        setCursorPosition(RIGHTBORDER + (LENGTH - (RIGHTBORDER))/3 - 3 , i + 1);
        if(fabs(arr[i]) > 99999999999999)
        {
            setCursorPosition(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y - 1);
            setConsoleColor(COLORERROR);
            puts("Numbers are too big. Resetting...");
            initRandArray(arr, size, -10, 10);
            printArr(arr, size);
            break;
        }
        printf("%.2f", arr[i]);
    }
    setCursorPosition(SBInfo.dwCursorPosition.X, SBInfo.dwCursorPosition.Y);
    setConsoleColor(COLORDEF);
}
void initConsole()
{
    int i, j;
    int status = 0;
    size_t nOfElements =0;
    char buffer[100];
    char settings[100];
    time_t t;
    srand((unsigned) time(&t));
    sprintf(settings,"mode con:cols=%i lines=%i", LENGTH, HEIGHT);
    system(settings);
    do
    {
        system("cls");
        puts("Please write the size of the array (1..23)");
        printf(" >> ");
        fgets(buffer, 100,stdin);
        status = sscanf(buffer, "%u", &nOfElements);
    }
    while(!status || nOfElements < 1 || nOfElements > 23);
    double arr[nOfElements];
    system("cls");
    setCursorPosition((LENGTH - (RIGHTBORDER))/2, 1);
    printf("Type 'help' for commands");
    clearZone(RIGHTBORDER, 0, LENGTH - 1, HEIGHT - 2, COLORWORKBACK);
    clearZone(0, BOTBORDER, LENGTH - 1, HEIGHT - 1, COLORWORKCOM);
    setConsoleColor(COLORWORKCOM);
    setCursorPosition(LENGTH/3, BOTBORDER);
    printf("Command's action :");
    setConsoleColor(COLORWORKBACK);
    setCursorPosition(RIGHTBORDER + (LENGTH - (RIGHTBORDER))/3, 0);
    printf("Array : ");
    initRandArray(arr, nOfElements, -10, 10);
    printArr(arr, nOfElements);
    setConsoleColor(COLORDEF);
    setCursorPosition(0, 1);
    getCommand(arr, nOfElements);
}
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void getCommand(double arr[], size_t size)
{
    char buffer[100];
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &SBInfo);
    if(SBInfo.dwCursorPosition.Y > BOTBORDER - 3)
    {
        clearZone(0, 1, RIGHTBORDER - 1, BOTBORDER - 2, COLORDEF);
        setCursorPosition(0, 1);
    }
    printf(" >> ");
    fgets(buffer, 100,stdin);
    if(!strcmp(buffer, "help\n"))
    {
        if(SBInfo.dwCursorPosition.Y > BOTBORDER - 20)
        {
            clearZone(0, 1, RIGHTBORDER - 1, BOTBORDER - 2, COLORDEF);
            setCursorPosition(0, 1);
        }
        puts(HELPINFO);
    }
    else if(!strcmp(buffer, "nullify\n"))
    {
        nullifyArr(arr, size);
        printArr(arr, size);
    }
    else if(strstr(buffer, "change"))
    {
        unsigned int index;
        int status;
        double value;
        printArr(arr, size);
        status = sscanf(buffer, "change %u %lf", &index, &value);
        if(status==2 && index < size)
        {
            changeNumByInd(arr, size, index, value);
            printArrEl(arr, size, index);
        }
        else
        {
            setConsoleColor(COLORERROR);
            puts("Inappropriate format");
            setConsoleColor(COLORDEF);
        }

    }
    else if(strstr(buffer, "random"))
    {
        double from, to;
        int status = sscanf(buffer, "random %lf %lf", &from, &to);
        if(status==2)
        {
            initRandArray(arr, size, from, to);
            printArr(arr, size);
        }
        else
        {
            setConsoleColor(COLORERROR);
            puts("Inappropriate format");
            setConsoleColor(COLORDEF);
        }
    }
    else if(!strcmp(buffer, "reverse\n"))
    {
        int i;
        reverseArr(arr, size);
        clearZone(RIGHTBORDER, 0, LENGTH - 1, 0, COLORSELECT);
        setConsoleColor(COLORSELECT);
        setCursorPosition(RIGHTBORDER + 1, 0);
        printf("REVERSED array : ");
        printArr(arr, size);
        setCursorPosition(0, SBInfo.dwCursorPosition.Y + 1);
        puts("Press anything to reverse back...");
        getch();
        setConsoleColor(COLORSELECT);
        clearZone(RIGHTBORDER, 0, LENGTH - 1, 0, COLORWORKBACK);
        setCursorPosition(RIGHTBORDER + (LENGTH - (RIGHTBORDER))/3, 0);
        setConsoleColor(COLORWORKBACK);
        printf("Array : ");
        clearZone(0, SBInfo.dwCursorPosition.Y + 1,RIGHTBORDER - 1, SBInfo.dwCursorPosition.Y + 1, COLORDEF);
        setCursorPosition(0, SBInfo.dwCursorPosition.Y + 1);
        reverseArr(arr, size);
        printArr(arr, size);
    }
    else if(!strcmp(buffer, "sum\n"))
    {
        double sum = findSum(arr, size);
        clearZone(0, BOTBORDER + 3, LENGTH - 1, BOTBORDER + 3, COLORWORKCOM);
        setCursorPosition(LENGTH/4, BOTBORDER + 3);
        setConsoleColor(COLORWORKCOM);
        printf("The sum of the array is : %.2f", sum);
        setConsoleColor(COLORDEF);
        setCursorPosition(0, SBInfo.dwCursorPosition.Y + 1);
    }
    else if(!strcmp(buffer, "nnegative\n"))
    {
        int nnegative = numOfNegElements(arr, size);
        clearZone(0, BOTBORDER + 3, LENGTH - 1, BOTBORDER + 3, COLORWORKCOM);
        setCursorPosition(LENGTH/4, BOTBORDER + 3);
        setConsoleColor(COLORWORKCOM);
        printf("The number of negative elements of the array is : %i", nnegative);
        setConsoleColor(COLORDEF);
        setCursorPosition(0, SBInfo.dwCursorPosition.Y + 1);
    }
    else if(strstr(buffer, "shift"))
    {
        unsigned int nSH;
        int status = sscanf(buffer, "shift %u", &nSH);
        if(status)
        {
            shiftArrR(arr, size, nSH);
            printArr(arr, size);
        }
        else
        {
            setConsoleColor(COLORERROR);
            puts("Inappropriate format");
            setConsoleColor(COLORDEF);
        }
    }
    else if(strstr(buffer, "cyclesh"))
    {
        unsigned int nSH;
        int status = sscanf(buffer, "cyclesh %u", &nSH);
        if(status)
        {
            cycleShiftArrR(arr, size, nSH);
            printArr(arr, size);
        }
        else
        {
            setConsoleColor(COLORERROR);
            puts("Inappropriate format");
            setConsoleColor(COLORDEF);
        }
    }
    else if(strstr(buffer, "powall"))
    {
        double power;
        int status = sscanf(buffer, "powall %lf", &power);
        if(status)
        {
            powEachElement(arr, size, power);
            printArr(arr, size);
        }
        else
        {
            setConsoleColor(COLORERROR);
            puts("Inappropriate format");
            setConsoleColor(COLORDEF);
        }
    }
    else if(!strcmp(buffer, "firstmin\n"))
    {
        int imin = getMinimumIndex(arr, size);
        printArr(arr, size);
        printArrEl(arr, size, imin);
        clearZone(0, BOTBORDER + 3, LENGTH - 1, BOTBORDER + 3, COLORWORKCOM);
        setCursorPosition(LENGTH/4, BOTBORDER + 3);
        setConsoleColor(COLORWORKCOM);
        printf("The index and value of first minimum element is : %i, %.2f", imin, arr[imin]);
        setConsoleColor(COLORDEF);
        setCursorPosition(0, SBInfo.dwCursorPosition.Y + 1);
    }
    else if(!strcmp(buffer, "swapmaxmin\n"))
    {
        int swap1, swap2;
        printArr(arr, size);
        swapLastMaxAndMin(arr, size, &swap1, &swap2);
        printArrEl(arr, size, swap1);
        printArrEl(arr, size, swap2);
    }
    else if(!strcmp(buffer, "exit\n"))
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        puts("Command not found. Check help");
    }
    getCommand(arr, size);
}

