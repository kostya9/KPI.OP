#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
void initRandArray(double arr[], size_t size)
{
    time_t t;
    srand((unsigned) time(&t));
    int i;
    for(i = 0; i < size; i++)
        arr[i] = rand()%100 * pow(10, -(rand()%3)) - 10;
}
void nullifyArr(double arr[], size_t size)
{
    int i;
    for(i = 0; i < size; i++)
        arr[i] = 0;
}
void changeNumByInd(double arr[], size_t size, int index, double number)
{
    arr[index] = number;
}
double findSum(double arr[], size_t size)
{
    int i,sum = 0;
    for(i = 0; i < size; i++)
        sum+=arr[i];
    return sum;
}
int numOfNegElements(double arr[], size_t size)
{
    int i, n = 0;
    for(i = 0; i < size; i++)
        if(arr[i] < 0)
            n++;
    return n;
}
void shiftArrR(double arr[], size_t size, int nSR)
{
    int i;
    for(i = size; i >=0; i--)
        if(i < nSR)
            arr[i] = 0;
        else
            arr[i] = arr[i - nSR];
}
void cycleShiftArrR(double arr[], size_t size, int nSR)
{
    int i, k;
    for(i = 0; i < nSR; i++)
        for(k = size - 1; k > 0; k--)
        {
            double temp = arr[k];
            arr[k] = arr[k - 1];
            arr[k - 1] = temp;
        }
}
void powEachElement(double arr[], size_t size, double power)
{
    int i;
    for(i = 0; i < size; i++)
        arr[i] = pow(arr[i], power);
}
int getMinimumIndex(double arr[], size_t size)
{
    int i;
    int iMin = 0;
    double nMin = arr[0];
    for(i = 1; i < size; i++)
        if(arr[i] < nMin)
        {
            iMin = i;
            nMin = arr[i];
        }
    return iMin;
}
void swapLastMaxAndMin(double arr[], size_t size)
{
    int i;
    int iMin = 0;
    int iMax = 0;
    double nMin = arr[0];
    double nMax = nMin;
    for(i = 1; i < size; i++)
        if(arr[i] <= nMin)
        {
            iMin = i;
            nMin = arr[i];
        }
        else if(arr[i] >= nMax)
        {
            iMax = i;
            nMax = arr[i];
        }
    double temp = arr[iMax];
    arr[iMax] = arr[iMin];
    arr[iMin] = temp;
}
void reverseArr(double arr[], size_t size)
{
    int i;
    for(i = 0; i <= size/2; i++)
    {
        double temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}
