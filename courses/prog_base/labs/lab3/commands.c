#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "commands.h"
#include "arrFuncs.h"
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void clearCommandPanel(int from, int to)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int columns, rows;
    int i, k;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    for(i = 0; i < to - from; i++)
        for(k = 0; k < columns; k++)
        {
            setCursorPosition(k, from + i);
            printf(" ");
        }
    setCursorPosition(0, from);
}
void printArray(double arr[], size_t size)
{
    int i, j;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    clearCommandPanel(WORKZONE, COMMANDSACTIONS);
    setConsoleColor(WORKBACK);
    for(j = 0; j < 9; j++)
        for(i = TAB - 4; i < 37 + LENGTH/2; i++)
        {
            setCursorPosition(i, WORKZONE + j);
            printf(" ");
        }
    setCursorPosition( (LENGTH - TAB)/2, WORKZONE);
    puts("Our Array");
    setConsoleColor(WORKFOR);
    setCursorPosition(TAB, WORKZONE + 2);
    for(i = 0; i < size; i++)
    {
        GetConsoleScreenBufferInfo(hConsole, &SBInfo);
        if(SBInfo.dwCursorPosition.X > LENGTH - TAB - 5)
            setCursorPosition(TAB, WORKZONE + 3);
        printf("%.3lf ", arr[i]);
    }
    setConsoleColor(WORKBACK);
    setCursorPosition( (LENGTH - TAB)/2 - 3, WORKZONE + 4);
    puts("Command's action : ");
    setCursorPosition(0, 1);
    setConsoleColor(DEFCOLOR);
}
void printArrayTo(double arr[], size_t size, unsigned int where)
{
    int i;
    setCursorPosition(TAB, where);
    setConsoleColor(WORKFOR);
    for(i = 0; i < size; i++)
        printf("%.3lf ", arr[i]);
        setConsoleColor(DEFCOLOR);
    setCursorPosition(0, 1);
}
void initConsole()
{
    int i, j;
    int status = 0;
    size_t nOfElements =0;
    char buffer[100];
    char settings[100];
    sprintf(settings,"mode con:cols=%i lines=%i", LENGTH, HEIGHT);
    system(settings);
    do
    {
        system("cls");
        puts("Please write the size of the array (1..10)");
        printf(" >> ");
        fgets(buffer, 100,stdin);
        status = sscanf(buffer, "%u", &nOfElements);
    }
    while(!status || nOfElements < 1 || nOfElements > 10);
    setConsoleColor(DEFCOLOR);
    for(i = 0; i < LENGTH; i++)
        for(j = 0; j < HEIGHT; j++)
        {
            setCursorPosition(i, j);
            printf(" ");
        }
    double arr[nOfElements];
    system("cls");
    setCursorPosition(LENGTH/3, 0);
    puts("Type 'help' for commands");
    initRandArray(arr, nOfElements);
    printArray(arr, nOfElements);
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
    printf(" >> ");
    fgets(buffer, 100,stdin);
    clearCommandPanel(1, WORKZONE);
    if(!strcmp(buffer, "help\n"))
    {
        puts(HELPINFO);
    }
    else if(!strcmp(buffer, "nullify\n"))
    {
        nullifyArr(arr, size);
        printArray(arr, size);
    }
    else if(strstr(buffer, "change"))
    {
        unsigned int index;
        int status;
        double value;
        status = sscanf(buffer, "change %u %lf", &index, &value);
        if(status==2 && index < size)
        {
            changeNumByInd(arr, size, index, value);
            printArray(arr, size);
        }
        else
            puts("Inappropriate format");
    }
    else if(!strcmp(buffer, "random\n"))
    {
        initRandArray(arr, size);
        printArray(arr, size);
    }
    else if(!strcmp(buffer, "reverse\n"))
    {
        int i;
        printArray(arr, size);
        reverseArr(arr, size);
        printArrayTo(arr, size, COMMANDSACTIONS);
        reverseArr(arr, size);
        clearCommandPanel(1, 2);
    }
    else if(!strcmp(buffer, "sum\n"))
    {
        double sum = findSum(arr, size);
        printArray(arr, size);
        setCursorPosition(TAB, COMMANDSACTIONS);
        setConsoleColor(WORKFOR);
        printf("sum : ");
        printf("%.3lf", sum);
        setCursorPosition(0, 1);
        setConsoleColor(DEFCOLOR);
    }
    else if(!strcmp(buffer, "nnegative\n"))
    {
        int nnegative = numOfNegElements(arr, size);
        printArray(arr, size);
        setCursorPosition(TAB, COMMANDSACTIONS);
        setConsoleColor(WORKFOR);
        printf("number of negative elements : ");
        printf("%i", nnegative);
        setConsoleColor(DEFCOLOR);
        setCursorPosition(0, 1);
    }
    else if(strstr(buffer, "shift"))
    {
        unsigned int nSH;
        int status = sscanf(buffer, "shift %u", &nSH);
        if(status)
        {
            shiftArrR(arr, size, nSH);
            printArray(arr, size);
        }
        else
            puts("Inappropriate format");
    }
    else if(strstr(buffer, "cyclesh"))
    {
        unsigned int nSH;
        int status = sscanf(buffer, "cyclesh %u", &nSH);
        if(status)
        {
            cycleShiftArrR(arr, size, nSH);
            printArray(arr, size);
        }
        else
            puts("Inappropriate format");
    }
    else if(strstr(buffer, "powall"))
    {
        double power;
        int status = sscanf(buffer, "powall %lf", &power);
        if(status)
        {
            powEachElement(arr, size, power);
            printArray(arr, size);
        }
        else
            puts("Inappropriate format");
    }
    else if(!strcmp(buffer, "firstmin\n"))
    {
        int ifmin = getMinimumIndex(arr, size);
        printArray(arr, size);
        setConsoleColor(WORKFOR);
        setCursorPosition(TAB, COMMANDSACTIONS);
        printf("Index and value of the first minimal element : ");
        printf("%i %.3lf", ifmin, arr[ifmin]);
        setConsoleColor(DEFCOLOR);
        setCursorPosition(0, 1);
    }
    else if(!strcmp(buffer, "swapmaxmin\n"))
    {
        swapLastMaxAndMin(arr, size);
        printArray(arr, size);
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

