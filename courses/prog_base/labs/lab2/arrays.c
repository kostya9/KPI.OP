#include <stdlib.h>
#ifdef max
#undef max
#endif
/* Заповнює масив випадковими цілими числами в діапазоні [0..1] (включно) */
void fillRand3(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rand() % 2;
}
/* Перевіряє чи всі елементи масиву знаходяться у діапазоні [0..1] (включно). Повертає 1, якщо умова задовольняється і 0 - якщо не задовольняється */
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
/* Знаходить максимальний серед елементів масиву */
int max(int arr[], int size)
	{	
		int i;
		int max = arr[0];
		for (i = 1; i < size; i++)
			max = max>arr[i] ? max : arr[i];
		return max;
	}
/* Знаходить індекс першого максимального елемента масиву */
int maxIndex(int arr[], int size)
{
	int i;
	int m = max(arr, size);
	for (i = 0; i < size; i++)
		if (arr[i] == m)
			return i;
}
/* Знаходить значення, яке найчастіше зустрічається у масиві. Якщо таких декілька, повертає більше з них*/
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
/* Розміри arr1, arr2 і res одинакові. Перевіряється різниця між відповідними елементами масивів arr1 і arr2. Ця різниця записується у відповідний елемент масиву res. Якщо всі різниці рівні 0 (тобто масиви arr1 і arr2 одинакові, то функція повертає 1, інакше - 0 */
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
/* Розміри arr1, arr2 і res одинакові. Виконати відповідну арифметичну операцію над елементами масивів arr1 і arr2 і записати у відповідний елемент масиву res результат. */

// Якщо n0 % 4 == 0
/* сума */
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
/* Розміри arr1, arr2 і res одинакові. Виконати відповідну логічну операцію над елементами масивів arr1 і 
arr2 і записати результат у масив res. Всі елементи масиву знаходяться у діапазоні [0..1] (включно) */
/* lor - logical OR */
void lor(int arr1[], int arr2[], int res[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		res[i] = arr1[i] | arr2[i];
	}
}