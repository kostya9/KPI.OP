#include <windows.h>
#include <stdio.h>
#include "console.h"
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void getConsoleAttributes(int * rows, int * columns)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void setFontSize(int x, int y)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX conFont = {0};
    conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    BOOL i = GetCurrentConsoleFontEx(hConsole,0,&conFont);
    if(!i)
        return GetLastError();
    conFont.dwFontSize.Y = y;
    conFont.dwFontSize.X = x;
    conFont.FontWeight = 100;
    conFont.FontFamily = FF_ROMAN;
    i = SetCurrentConsoleFontEx(hConsole, 0, &conFont);
    if(!i)
        return GetLastError();
}
Player * getScoreBoard(int * n)
{
     FILE * scoreboardFile = fopen("score.txt", "r");
    int status;
    if(scoreboardFile==NULL)
        return NULL;
    char buff[100];
    int i;
    char nOfPlayers = 0;
    fgets(buff, 100, scoreboardFile);
    sscanf(buff, "%i", &nOfPlayers);
    Player * players = (Player *)malloc(nOfPlayers * sizeof(Player));
    for(i = 0; i < nOfPlayers; i++)
    {
        fgets(buff, 100, scoreboardFile);
        status = sscanf(buff, "%i %s", &(players[i].points), players[i].name);
        if(status!=2)
        {
            fclose(scoreboardFile);
            free(players);
            return NULL;
        }
    }
    fclose(scoreboardFile);
    *n = nOfPlayers;
    return players;
}
void addToScoreBoard(Player * player, int * nOfPlayers)
{
    FILE * scoreboardFile= fopen("score.txt", "r+");
    (*nOfPlayers)++;
    fprintf(scoreboardFile, "%i\n",*nOfPlayers);
    fseek(scoreboardFile, 0, SEEK_END);
    fprintf(scoreboardFile, "\n%i %s", player->points, player->name);
    fclose(scoreboardFile);
}
void initScoreBoard(Player * players, int nOfPlayers)
{
    int i;
    setConsoleColor(COLORDEF);
    system("cls");
    puts("SCOREBOARD : ");
    printf("%20s %10s\n", "NAME", "SCORE");
    for(i = 0; i < nOfPlayers; i++)
        printf("%20s %10i\n", players[i].name, players[i].points);
    puts("Press anything to continue");
    getch();
}
void initInterface(Player * players, int nOfPlayers)
{
    char name[100];
    char buff[100];
    int points;
    int level, curY = 0;
    int status = 0;
    system("mode con:cols=50 lines=50");
    system("cls");
    setFontSize(15, 20);
    if(nOfPlayers > 0)
        initScoreBoard(players, nOfPlayers);
    strcpy(name, "DEFAULT");
    system("cls");
    setCursorPosition(CONSOLESIZE/2 - 10,curY++);
    puts("Write your name:");
    setCursorPosition(CONSOLESIZE/2 - 15,curY++);
    fgets(buff, 100, stdin);
    buff[strlen(buff) - 1] = '\0';
    if(strlen(buff)>1)
        strcpy(name, buff);
    while(!status)
    {
        printf("Hi, %s, what level do you want to take? (0..9)\n", name);
        fgets(buff, 100, stdin);
        status = sscanf(buff, "%i", &level);
        if(!status || level>9 || level < 0)
        {
            status = 0;
            puts("Try again:");
            curY++;
        }
    }
    puts("Press anything to start...");
    getch();
    curY = 0;
    points = initSnake(level);
    setConsoleColor(COLORDEF);
    setCursorPosition(0,curY++);
    Player p;
    strcpy(p.name, name);
    p.points = points;
    printf("HOORAY! You've got %i points. Type YES if you want to restart. Type SCORE if you want to see the scoreboard previously. Type anything else if you want to stop\n", points);
    addToScoreBoard(&p, &nOfPlayers);
    fgets(buff, 100, stdin);
    if(!strcmp(buff, "YES\n"))
        initInterface(players, nOfPlayers);
    else if(!strcmp(buff, "SCORE"))
    {
        initScoreBoard(players, nOfPlayers);
        initInterface(players, nOfPlayers);
    }


}

