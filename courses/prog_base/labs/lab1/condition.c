#include <math.h>
int satisfies(int a, int b, int c)
{
    if (a < 0 && b < 0 && c < 0)
    {
        int min;
        int sum;
        if (a < b && a < c)
            min = a;
        else if (b < a&& b < c)
            min = b;
        else if (c < b && c < a)
            min = c;
        sum = a + b + c - min;
        min = abs(min);
        

        else if(sum<-256 && (min&(min-1)==0) && min<256)
            return 1;
        else if ((abs(sum)-min)<16||abs(sum)<16)
            return 1;
        else
            return 0;
    }
    else if (a<0 || b<0 || c<0)
    {
        if ((a<0 && b>=0 && c>=0)|| (b<0 && a >= 0 && c >= 0)|| (c<0 && b >= 0 && a >= 0))
        {
            if (a < 0)
                return a < -256;
            else if (b < 0)
                return b < -256;
            else if (c < 0)
                return c < -256;
        }
        else
        {
            if (a*b>0)
                return (a + b)*(1 + 8)>-256;
            else if(b*c>0)
                return (b + c)*(1 + 8)>-256;
            else if(a*c>0)
                return (a + c)*(1 + 8)>-256;
        }
    }
    else
    {
        int max;
        int min;
        if (a >= b && a >= c)
            max = a;
        else if (b >= a && b >= c)
            max = b;
        else if (c >= b && c >= a)
            max = c;
        if (a <= b && a <= c)
            min = a;
        else if (b <= a && b <= c)
            min = b;
        else if (c <= b && c <= a)
            min = c;
        if (min == 0)
            return 0;
        else
            return max%min == 0;

    }
}
