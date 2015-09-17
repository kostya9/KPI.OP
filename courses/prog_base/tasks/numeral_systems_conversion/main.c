#include <stdio.h>
#include <stdlib.h>
char* alphabet[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','G','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char* output[999];
int indexOf(char element)
{
    int i;
    for(i = 0; i<36;i++)
    {
        if(alphabet[i]==element)
            return i;
    }
}
int convertToTen(char* num, unsigned int sourceBase)
{
    int numberBaseNInt[999];
    int i = 0;
    while(num[i]!='\0')
    {
        numberBaseNInt[i] = indexOf(num[i]);
        i++;
    }
    int n;
    int result = 0;
    for(n=0;n<i;n++)
    {
        int j;
        int base = 1;
        for(j=0;j<n;j++)
            base*=sourceBase;
        int numb = numberBaseNInt[i-n-1];
        result+= numb * base;
    }
    return result;
}
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{
    char* converted[9999];
    unsigned int k = convertToTen(number,sourceBase);
    int i = 0;
    while(!(k<destBase))
    {
        converted[i]=(char)(k%destBase);
        k/=destBase;
        i++;
    }
    converted[i]=(char)k;
    int n;
    int b = 0;
    int ten = 1;
    for(n=0;n<i+1;n++)
    {

        b+=ten*(int)converted[n];
        ten *= 10;
    }
   // output[i+1]='\0';
    return b;
}
int main()
{
    int c;
    c = ns_convert("10",2,10);
    printf("\n");
    printf("Hello world!\n Number is %i", c);
    return 0;
}






