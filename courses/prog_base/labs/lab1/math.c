#include <math.h>
double calc(double x, double y, double z)
{
    double a;
    if(x!=y && x!=0 && (x>=y ||((z - (int)(z))==0 && ((int)(z))%2!=0)))
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
