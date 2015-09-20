#include <stdio.h>
#include <stdlib.h>
char start = 48;
char startL = 48+7;
int convertToTen(char* num, unsigned int sourceBase)
{
    int numberBaseNInt[999];
    int i = 0;
    while(num[i]!='\0')
    {
        if(num[i]>start+9)
           numberBaseNInt[i] = num[i] - startL;
        else
            numberBaseNInt[i] = num[i] - start;
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
        int numb =numberBaseNInt[i-n-1];
        result+= numb * base;
    }
    return result;
}
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{

    char converted[64];
    unsigned int k = convertToTen(number,sourceBase);
    int z = 0;
    while(!(k<destBase))
    {
        int mod = k%destBase;
        if(mod>9)
           converted[z]=startL + mod;
        else
           converted[z]=start + mod;
        k/=destBase;
        z++;
    }
    if(k> 9)
        converted[z]=startL + k;
    else
        converted[z]=start + k;
    int n;
    char temp;
    for(n=0;n<z/2+1;n++)
    {
        temp = converted[n];
        converted[n] = converted[z-n];
        converted[z-n]=temp;
    }
    char* result=(char *)malloc((z + 2) * sizeof(char));
    for(n=0;n<z+1;n++)
        result[n]=converted[n];
    result[z+1]='\0';
    return result;
}
int main()
{
    char* c = ns_convert("A1", 16,10);
    printf("\nHello world!\n Number is %s", c );
    free(c);
    return 0;
}
