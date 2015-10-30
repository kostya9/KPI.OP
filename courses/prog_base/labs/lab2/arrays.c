#include <stdlib.h>
#ifdef max
#undef max
#endif
void fillRand3(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rand() % 2;
}
int checkRand3(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if ((arr[i]%10)>1)
			return 0;
	}
	return 1;
}
float meanValue(int arr[], int size)
{
    int i;
    float sum = 0;
    for(i = 0; i<size; i++)
        sum+=arr[i];
    return sum/size;
}
int max(int arr[], int size)
	{
		int i;
		int max = arr[0];
		for (i = 1; i < size; i++)
			max = max>arr[i] ? max : arr[i];
		return max;
	}
int meanIndex(int arr[], int size)
{
    int i;
    float mean = meanValue(arr, size);
    int iMean = 0;
    float deltaMean = fabs(arr[0] - mean);
    for(i=1;i<size; i++)
    {
        float curDeltaMean = fabs(mean - arr[i]);
        if(curDeltaMean<deltaMean)
        {
            iMean = i;
            deltaMean = curDeltaMean;
        }
    }
    return iMean;
}
int maxIndex(int arr[], int size)
{
	int i;
	int m = max(arr, size);
	for (i = 0; i < size; i++)
		if (arr[i] == m)
			return i;
}
int maxOccurance(int arr[], int size)
{
	int prevMaxOccur[2] = { 0, -1 }; // 0 - number, 1 - number of occurances
	int i, k;
	for(i=0;i<size;i++)
    {
        int curNOccur = 0;
        for(k=0;k<size;k++)
            if(arr[i]==arr[k])
                curNOccur++;
        if(prevMaxOccur[1]==curNOccur)
        {
            prevMaxOccur[0] = prevMaxOccur[0]>arr[i] ? prevMaxOccur[0] : arr[i];
            prevMaxOccur[1] = curNOccur;
        }
        else if(prevMaxOccur[1]<curNOccur)
        {
            prevMaxOccur[0] = arr[i];
            prevMaxOccur[1] = curNOccur;
        }

    }
    return prevMaxOccur[0];
}
int diff(int arr1[], int arr2[], int res[], int size)
{
	int i;
	int isEqual = 1;
	for (i = 0; i < size; i++)
	{
		res[i] = arr1[i] - arr2[i];
		if (res[i] != 0)
			isEqual = 0;
	}
	return isEqual;
}
void add(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		res[i] = arr1[i] + arr2[i];
	}
}
int lteq(int arr1[], int arr2[], int size)
{
	int isLessOrEqauals = 1;
	int i;
	for (i = 0; i < size; i++)
	{
		if (arr1[i] > arr2[i])
			isLessOrEqauals = 0;
	}
	return isLessOrEqauals;
}
void lor(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		res[i] = arr1[i] | arr2[i];
	}
}
