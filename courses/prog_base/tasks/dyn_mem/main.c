#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
int main(void)
{
    char * buff = (char *)malloc(sizeof(char) * 100);
    int * i = (int *)malloc(sizeof(int));
    char * fSym = (char *)malloc(sizeof(char));
    char * fNum = (char *)malloc(sizeof(char));
    char * sSym = (char *)malloc(sizeof(char));
    char * sNum = (char *)malloc(sizeof(char));
    *i = 100;
    *fSym = -1;
    puts("Write a string please");
    fgets(buff, *i, stdin);
    for(*i = 0; *i < strlen(buff) - 1; (*i)++)
        if((isalpha(buff[*i]) && tolower(buff[*i])<='f' && tolower(buff[*i])>='a') || (isdigit(buff[*i])  && buff[*i]>='0' && buff[*i]<='9'))
        {
            *sSym = *i;
            if(*fSym==-1)
                *fSym = *i;
        }
    if(*fSym!=-1)
    {
        *fSym = tolower(buff[*fSym]);
        *sSym = tolower(buff[*sSym]);
        *fNum = isdigit(*fSym) ? (*fSym - '0') : (10 + (*fSym) -  'a');
        *sNum = isdigit(*sSym) ? (*sSym - '0') : (10 + (*sSym) -  'a');
        printf("The greatest number from %c(%i) and %c(%i) is %i", *fSym, *fNum, *sSym, *sNum, *fNum > *sNum ? *fNum : *sNum);
    }
    else
        puts("There is no 16-based symbols");
    free(buff);
    free(i);
    free(fSym);
    free(sSym);
    free(fNum);
    free(sNum);
    return EXIT_SUCCESS;
}
