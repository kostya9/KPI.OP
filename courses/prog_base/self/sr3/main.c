#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
    char * fName1;
    char * fName2;
    FILE * fp1;
    FILE * fp2;
    int isEmail = 0;
    int countAfterDot = 0;
    int count = 0;
    char c;
    char curStr[100];
    if(argc>2)
    {
        fName1 = argv[1];
        fName2 = argv[2];
        puts("Your files are :");
        puts(argv[1]);
        puts(argv[2]);
    }
    fp1 = fopen(fName1, "r");
    fp2 = fopen(fName2, "w");
    if(fp1 == NULL)
    {
        puts("ERROR : File 1 doesnt exist");
        return EXIT_FAILURE;
    }
    else if(fp2 == NULL)
    {
        puts("ERROR : File 2 doesnt exist");
        return EXIT_FAILURE;
    }
    while((c=fgetc(fp1))!=EOF)
    {
        curStr[count] = c;
        if(c==' '|| c=='\n' && !isEmail)
            count = 0;
        else if(c=='@' && !isEmail)
        {
            isEmail=1;
            count++;
        }
        else if(c=='.')
        {
            countAfterDot++;
            count++;
        }
        else if(c==' ' || c=='\n' && isEmail)
        {
            curStr[count] = '\0';
            countAfterDot--;
            if(countAfterDot>=2 && countAfterDot<=4)
            {
                fputs(curStr, fp2);
                fputs("\n", fp2);
            }
            count = 0;
            isEmail = 0;
            countAfterDot = 0;
        }
        else if(isdigit(c) || isalpha(c) || c=='.' || c=='_'|| c=='%'|| c=='+'|| c=='-')
        {
            if(countAfterDot>0 && !isalpha(c))
            {
                countAfterDot = 0;
                count = 0;
                isEmail = 0;
            }
            else if(countAfterDot>0)
            {
                countAfterDot++;
                count++;
            }
            else
                count++;
        }
        else
            count = 0;
    }
    puts("Success");
    return EXIT_SUCCESS;
}

