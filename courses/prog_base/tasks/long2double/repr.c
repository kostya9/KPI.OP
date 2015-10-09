#include <math.h>
double long2double(long long longNum)
{
	if (longNum == NAN)
		return NAN;
	else if (longNum == INFINITY)
		return INFINITY;
	else
		return *((double *)&longNum);
}