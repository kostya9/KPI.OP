#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*void setCursorPosition(int x, int y)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}
void animatedText(char * text, int step, int nOfLines)
{
    int x = 0;
    if(nOfLines>1)
        nOfLines--;
    else return;
    int k, state = 0;
    int l = nOfLines;
    int prevL;
    for(x = 0; x < 120 - strlen(text); x+=step)
    {
        usleep(1000 * 100);
        if(x>1)
        {
            setCursorPosition(x-step, prevL);
            printf("-");
            for(k=0; k<strlen(text) - 1; k++)
                printf(" ");
        }
        setCursorPosition(x, l);
        puts(text);
        prevL = l;
        if(l==nOfLines)
            state = 1;
        else if(l == 0)
            state = 0;
        if(state)
            l--;
        else
            l++;
    }
}
void initializeAnimatedTest()
{
    int nOfLines, step;
    puts("Write the step:");
    scanf("%i", &step);
    puts("Write number of lines");
    scanf("%i", &nOfLines);
    char word[30];
    puts("Write the words whick will jump(<30 symbols)");
    scanf("%s", &word);
    system("cls");
    animatedText(word, step, nOfLines);
    getchar();
}*/
