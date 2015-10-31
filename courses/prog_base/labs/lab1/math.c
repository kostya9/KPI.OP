#include <math.h>
double calc(double x, double y, double z)
{
    double a;
    if(x!=y && x!=0 && ( x>=y || ((int)(1/z) - (1/z))==0))
    {
        a = pow(x, y + 1) / pow(x - y, 1 / z);
        a += 8*y + z / x;
        a += sqrt(fabs(cos(y) / sin(x) + 1));
    }
    else
    {
        return NAN;
    }
    return a;
}
