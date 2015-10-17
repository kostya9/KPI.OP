#include <stdlib.h>
#ifdef max
#undef max
#endif
/* �������� ����� ����������� ������ ������� � ������� [0..1] (�������) */
void fillRand3(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rand() % 2;
}
/* �������� �� �� �������� ������ ����������� � ������� [0..1] (�������). ������� 1, ���� ����� ��������������� � 0 - ���� �� ��������������� */
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
/* ��������� ������������ ����� �������� ������ */
int max(int arr[], int size)
	{	
		int i;
		int max = arr[0];
		for (i = 1; i < size; i++)
			max = max>arr[i] ? max : arr[i];
		return max;
	}
/* ��������� ������ ������� ������������� �������� ������ */
int maxIndex(int arr[], int size)
{
	int i;
	int m = max(arr, size);
	for (i = 0; i < size; i++)
		if (arr[i] == m)
			return i;
}
/* ��������� ��������, ��� ��������� ����������� � �����. ���� ����� �������, ������� ����� � ���*/
int maxOccurance(int arr[], int size)         //@todo DIRTY AF
{
	int maxOccur[2] = { arr[0], 1 }; // 0 - number, 1 - number of occurances
	int occs[10][2];// 0 - number, 1 - number of occurances
	occs[0][0] = arr[0];
	occs[0][1] = 1;
	int i;
	int n;
	for (i = 1; i < size; i++)
	{
		occs[i][0] = arr[i];
		occs[i][1] = 1;
		for (n = 0; n < size; n++)
		{
			if (arr[i] == occs[n][0])
				occs[n][1]++;
		}
	}
	for (i = 1; i < size; i++)
	{
		if (occs[i][1]>maxOccur[1] || (occs[i][1] == maxOccur[1] && occs[i][0]>maxOccur[0]))
		{
			maxOccur[0] = occs[i][0];
			maxOccur[1] = occs[i][1];
		}
	}
	return maxOccur[0];
}
/* ������ arr1, arr2 � res ��������. ������������ ������ �� ���������� ���������� ������ arr1 � arr2. �� ������ ���������� � ��������� ������� ������ res. ���� �� ������ ��� 0 (����� ������ arr1 � arr2 ��������, �� ������� ������� 1, ������ - 0 */
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
/* ������ arr1, arr2 � res ��������. �������� �������� ����������� �������� ��� ���������� ������ arr1 � arr2 � �������� � ��������� ������� ������ res ���������. */

// ���� n0 % 4 == 0
/* ���� */
void add(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		res[i] = arr1[i] + arr2[i];
	}
}
/* lteq - less than or equals */
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
/* ������ arr1, arr2 � res ��������. �������� �������� ������ �������� ��� ���������� ������ arr1 � 
arr2 � �������� ��������� � ����� res. �� �������� ������ ����������� � ������� [0..1] (�������) */
/* lor - logical OR */
void lor(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		res[i] = arr1[i] | arr2[i];
	}
}