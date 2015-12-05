#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
int isVowel(char c)
{
    c = tolower(c);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return 1;
    else
        return 0;
}
int nOfVowel(char * buffer, size_t stringLength)
{
    if(stringLength==0)
        return 0;
    else
        return isVowel(*buffer) + nOfVowel(buffer + 1, stringLength - 1);
}
int main(void)
{
    char buffer[100];
    puts("Enter the string : ");
    fgets(buffer, 100, stdin);
    printf("There were %i vowels in the string", nOfVowel(buffer, strlen(buffer)));
    return EXIT_SUCCESS;
}
