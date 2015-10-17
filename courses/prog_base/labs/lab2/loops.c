#include <math.h>
double calc(int n, int m)
{
	int answer = 0;
	int countN;
	int countM;
	for (countN = 0; countN < n; countN++)
		for (countM = 0; countM < m; countM++)
		{
			answer += sqrt(countN + countM * (1 + 2));
		}
}