#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"
#include "console.h"

int main(void)
{
    int nOfPlayers;
    Player * players = getScoreBoard(&nOfPlayers);
    initInterface(players, nOfPlayers);
    if(nOfPlayers > 0)
        free(players);
    setConsoleColor(COLORDEF);
    return EXIT_SUCCESS;
}
