#include <stdio.h>
#include <stdlib.h>
char* alphabet[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','G','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
int indexOf(char element)
{
    int j = alphabet[10];
    int i;
    for(i = 0; i<36;i++)
    {
        if(alphabet[i]==element)
            return i;
    }
    return "37";
}
double convertToTen(char* num, unsigned int sourceBase)
{
    int numberBaseNInt[999];
    int i = 0;
    while(num[i]!='\0')
    {
        numberBaseNInt[i] = indexOf(num[i]);
        i++;
    }
    int n;
    double result = 0;
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
int main()
{
    printf ("%f",10^0);
    printf("\n");
    double k = convertToTen("77765",8);
    printf("Hello world!\n Number is ");
    printf("%f",k);
    return 0;
}

/*
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{
    char* output;
    if(sourceBase!=10)
    {
        number = convertToTen(number,sourceBase);
    }
    while(!number<destBase)
    {
        // output+=number%destBase;
        //  number/=destBase;
    }

    return "r";
}
*/


