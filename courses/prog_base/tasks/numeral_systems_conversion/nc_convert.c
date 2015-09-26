#include <stdio.h>
#include <math.h>
char getIntOrChar(char c, int intOrChar)
{
    if(intOrChar==0)
    {
        if(c>48+9)
            return c -('0'+7);
        else
            return c - '0';
    }
    else
    {
        if(c>9)
            return c +('0'+7);
        else
            return c + '0';
    }
}
double doubleToTenDouble(char* number, unsigned int sourceBase)
{
    double doubleTen=0;
    signed int i = 0;
    while(number[i*(-1)]!='\0')
    {
        doubleTen+=getIntOrChar(number[i*(-1)],0)*pow(sourceBase, i-1);
        i--;
    }
    return doubleTen;
}
int intToTenInt(char* number, unsigned int sourceBase, unsigned int length)
{
    int intTen=0;
    int i = 0;
    while(number[i]!='\0')
    {
        intTen+=getIntOrChar(number[length-i-1],0)*pow(sourceBase, i);
        i++;
    }
    return intTen;
}
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{
    char cDouble[64 * sizeof(char)];
    char cInteg[64* sizeof(char)];
    double dNum;
    int iNum;
    int isDouble = 0;
    int i=0;
    int length;
    while(number[i]!='\0')
    {
        if(number[i]=='.')
        {
            isDouble = 1;
            break;
        }
        else
            cInteg[i]=number[i];
        i++;
    }
    length = i;
    cInteg[i]='\0';
    if(isDouble)
    {
        i++;
        while(number[i-1]!='\0')
        {
            cDouble[i-length-1]=number[i];
            i++;
        }
        cDouble[i-length-1]='\0';
        dNum = doubleToTenDouble(cDouble, sourceBase) + intToTenInt(cInteg, sourceBase, length);
        iNum = (int)dNum;
        double d = dNum-iNum;
        for(i=0;i<12;i++)
        {
            d*=destBase;
            cDouble[i]=getIntOrChar((int)d, 1);
            d -=(int)d;
        }
        cDouble[i] = '\0';
        }
    else
            iNum = intToTenInt(cInteg, sourceBase, length);

    i=0;
    while(iNum>=destBase)
    {
        cInteg[i] = getIntOrChar(iNum%destBase,1);
        iNum/=destBase;
        i++;
    }
    cInteg[i]= getIntOrChar(iNum,1);
    cInteg[i+1]='\0';
    length = i+1;
    char* t = malloc(64*sizeof(char));
    i=0;
    while(cInteg[i]!='\0')
    {
        t[i]=cInteg[i];
        i++;
    }

    length = i-1;
    int n;
    char temp;
    for(n=0;n<length/2+1;n++)
    {
        temp = t[n];
        t[n] = t[length-n];
        t[length-n]=temp;
    }
    if(isDouble)
    {
        t[i]='.';
        i++;
        length=i;
        while(cDouble[i-length]!='\0')
            {
                t[i]=cDouble[i-length];
                i++;
            }
    }
    t[i]='\0';
    return t;
}
int main()
{
    char* c = ns_convert("1010100", 2,10);
    printf("\nHello world!\n Number is %s", c );
    free(c);
    return 0;
}
