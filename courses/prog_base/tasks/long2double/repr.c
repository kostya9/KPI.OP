#include <math.h>
double long2double(long long longNum)
{
	unsigned long long mask = 1;
	mask <<= 63;
	int count = 0;
	int sign = 0;
	short int exponent=0;
	double mantissa = 0;
	if (mask == (longNum&mask))
		sign = 1;
	mask >>= 1;
	count++;
	int powN = 10;
	for (count; count < 12; count++)
	{
		if (mask == (longNum&mask))
			exponent += pow(2, powN);
		powN--;
		mask >>= 1;
	}
	for (count; count < 64; count++)
	{
		if (mask == (longNum&mask))
			mantissa += pow(2, powN);
		powN--;
		mask >>= 1;
	}
	if (exponent == 2047 && mantissa > 0)
		return pow(-1, sign)*NAN;
	else if (exponent == 2047)
		return pow(-1, sign)*INFINITY;
	else if (exponent == 0 && mantissa == 0)
		return pow(-1, sign)*0.0;
	else if (exponent==0 && mantissa > 0)
		return pow(-1, sign)*pow(2,-1022) * (mantissa);
	else if(exponent>0 && exponent<2047)
		return pow(-1, sign)*pow(2, exponent - 1023) * (1 + mantissa);
}