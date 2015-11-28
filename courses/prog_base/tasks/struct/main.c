#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
typedef struct
{
    char name[100];
    char invitedStarName[100];
    int length;
} Episode;
int count(int size, Episode arr[size])
{
    int i, count = 0;
    for(i = 0; i < size; i++)
        if(arr[i].length > 30)
            count++;
    return count;
}
void change(Episode * pVar, const char * newValue)
{
    strcpy(pVar->name, newValue);
}

void print(Episode * pVar)
{
    printf("Episode name: %s\nInvited star : %s\nLength : %i\n", pVar->name, pVar->invitedStarName, pVar->length);
}
int main(void)
{
    int i;
    char buff[100];
    int status = 0;
    time_t t;
    system("mode con: lines=30");
    srand((unsigned) time(&t));
    Episode eps[3] = {{"First Invitation", "Kolly Serbens", rand()%60 + 1}, {"Strange Fury", "Mrs Robbinson Jr", rand()%60 + 1}, {"The Legalisation", "Mary Johnes and her father Mr Johnes", rand()%60 + 1}};
    printf("There are %i episodes which are longer that 30 minutes\n\n", count(3, eps));
    puts("Episodes are : \n");
    for(i = 0; i < 3; i++)
    {
        print(&eps[i]);
        puts("");
    }
    while(status!=1)
    {
        puts("\nType in the index of the element which you want to change(0..2)");
        fgets(buff, 100, stdin);
        status = sscanf(buff, "%i", &i);
        if(i > 2 || i < 0)
            status--;
    }
    change(&eps[i], "THIS IS SPARTA!!!11");
    puts("Okay. Here is your changed episode : \n");
    print(&eps[i]);
    return EXIT_SUCCESS;
}
