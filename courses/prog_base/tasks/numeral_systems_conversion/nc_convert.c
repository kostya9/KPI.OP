#include <stdio.h>
#include <stdlib.h>
char start = 48;
char startL = 48+7;
float pow(float source, int power)
{
    float f = source;
    int i;
    if(power == 1)
        return source;
    else if(power==0&&source!=0)
            return 1;
    else if(power>1)
        for(i=2;i<=power;i++)
            source*=f;
    else
        for(i=0;i>=power;i--)
            source/=f;
    if(source == 0)
        return 0;

    return source;
}
float convertFractionToTen(char* fraction, unsigned int sourceBase, unsigned int length)
{
    float fr = 0;
    int i=0;
    while(fraction[i]!='\0')
    {
        if(fraction[i]>start+9)
            fr += (fraction[i])*pow(sourceBase, -i-1);
        else
            fr += (fraction[i])*pow(sourceBase, -i-1);
        i++;
    }
    return fr;
}
float convertIntToTen(char* num, unsigned int sourceBase)
{
    int numberBaseNInt[999];
    int i = 0;
    float fr;
    char fraction[12];
    while(num[i]!='\0')
    {
        if(num[i]=='.')
        {
            fr=1;
            break;
        }
        if(num[i]>start+9)
           numberBaseNInt[i] = num[i] - startL;
        else
            numberBaseNInt[i] = num[i] - start;
        i++;
    }
        numberBaseNInt[i]='\0';
    int k;
    if(fr)
    {
        i++;
        k = i;

        do
        {
            if(num[i]>start+9)
                fraction[i-k] = num[i] - startL;
            else
                fraction[i-k] = num[i] - start;
            i++;
        }
        while(num[i]!='\0'&&i<k+12);
        fr=convertFractionToTen(fraction, sourceBase, i-k+1);
    }

    int n;
    int result = 0;
    for(n=0;n<k-1;n++)
    {
        int base;
        base = pow(sourceBase, n);
        int numb =numberBaseNInt[k-n-2];
        result+= numb * base;
    }
    return result+fr;
}
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{
    float fr;
    char converted[64];
    char fraction[12];
    float k = convertIntToTen(number,sourceBase);
    if(destBase==10)
    {
        char out[999];
        int kI = (int)k;
        int j = 0;
        if((int)k==0)
        {
            out[0]='0';
            j++;
        }
        else
            while(kI!=0)
            {
                int mod = (kI)%10;
                out[j]=start + mod;
                kI/=10;
                j++;
            }
        int n;
        char temp;
        for(n=0;n<(j-1)/2+1;n++)
        {
            temp = out[n];
            out[n] = out[(j-1)-n];
            out[(j-1)-n]=temp;
        }
        out[j]='.';
        j++;
        k=k-(int)k;
        while(k!=0)
        {
            k*=10;
            out[j] = start + k/1;
            k-=(int)k;
            j++;
        }
        out[j]='\0';
        return out;
    }
    unsigned int kInt = k/1;
    fr = k-kInt;
    int z = 0;
    while(!(kInt<destBase))
    {
        int mod = (kInt)%destBase;
        if(mod>9)
           converted[z]=startL + mod;
        else
           converted[z]=start + mod;
        kInt/=destBase;
        z++;
    }
    if(kInt> 9)
        converted[z]=startL + kInt;
    else
        converted[z]=start + kInt;
    int n;
    char temp;
    for(n=0;n<z/2+1;n++)
    {
        temp = converted[n];
        converted[n] = converted[z-n];
        converted[z-n]=temp;
    }

    char* result=(char *)malloc((z + 2+12) * sizeof(char));
    for(n=0;n<z+1;n++)
        result[n]=converted[n];
    int i;
    if(fr>0)
    {
        result[z+1]='.';

        for(i=0;i<12;i++)
        {
                fr*=destBase;
                int integ = fr/1;
                if(integ>9)
                result[z+i+2]=startL+ integ;
                else
                    result[z+i+2]=start + integ;
                fr=fr-integ;
        }
    }
    result[z+2+i]='\0';
    return result;
}
int main()
{
    char* c = ns_convert("A.AA", 16,8);
    printf("\nHello world!\n Number is %s", c );
    free(c);
    return 0;
}
