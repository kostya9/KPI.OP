#include <math.h>
double calc(double x, double y, double z)
{
	double a;
	a = pow(x, y + 1) / pow(x - y, 1 / z);
	a += 8*y + z / x;
	a += sqrt(fabs(cos(y) / sin(x) + 1));
	return a;
}