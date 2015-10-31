#include <math.h>
double calc(int n, int m)
{
	double answer = 0;
	int countN, countM;
	for (countN = 0; countN < n; countN++)
		for (countM = 0; countM < m; countM++)
			answer += sqrt(countN + countM * 3);
    return answer;
}
