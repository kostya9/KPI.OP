#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
char * sortAlpha(char * str, int sorted);
char * changeStr(char * str);
int main(int argc, char * argv[])
{
    int n;
    char buffer[100];
    char * fNameR;
    char * fNameW;
    FILE * fR;
    FILE * fW;
    if(argc > 1)
    {
        fNameR = argv[1];
        fR = fopen(fNameR, "r");
        fNameW = argv[2];
        fW = fopen(fNameW, "w");
        if(!fR || !fW)
        {
            fclose(fR);
            fclose(fW);
            puts("Files weren't found");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        puts("There were no files");
        exit(EXIT_FAILURE);
    }
    while(fgets(buffer, 100, fR))
    {
        changeStr(buffer);
        fputs(buffer, fW);
    }
    fclose(fR);
    fclose(fW);
    return EXIT_SUCCESS;
}
char * changeStr(char * str)
{
    int i, k, n = 0;
    char consonants[] = {'a', 'b', 'c', 'd','f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    size_t cCons = sizeof(consonants)/sizeof(consonants[0]);
    for(i = 0; i < strlen(str); i++)
        if(isalpha(str[i]))
        {
            str[i] = tolower(str[i]);
            for(k = 0; k < cCons; k++)
                if(str[i]==consonants[k])
                {
                    str[n] = str[i];
                    n++;
                }
        }
    str[n] = '\0';
    sortAlpha(str, 0);
    str[n] = '\n';
    str[n + 1] = '\0';
    return str;
}


char * sortAlpha(char * str, int sorted)
{
    if(sorted == strlen(str))
        return str;
    int ind = sorted + fCharMinInd(&str[sorted]);
    char temp = str[ind];
    str[ind] = str[sorted];
    str[sorted] = temp;
    sortAlpha(str, sorted + 1);
}
int fCharMinInd(char * str)
{
    int i;
    char minCons = 127;
    int minInd;
    for(i = 0; i < strlen(str); i++)
    {
        if(str[i] < minCons)
        {
            minInd = i;
            minCons = str[i];
        }
    }
    return minInd;
}
