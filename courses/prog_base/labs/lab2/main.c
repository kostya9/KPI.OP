#include "lab.h"
#include <time.h>
double calc(int n, int m);
void printArr(int arr[], int size)
{
    int i;
    for(i = 0; i<size; i++)
        printf("%i ", arr[i]);
    puts("");
}
void arrayTests()
{
    int arr[16];
    int arr1[16];
    int res[16];
    time_t t;
    int size = sizeof(arr)/sizeof(arr[0]);
    srand((unsigned) time(&t));
    fillRand3(arr, size);
    srand((unsigned) time(&t) + 1);
    fillRand3(arr1, size);
    printf("Array 1 was filled %scorrecly :\n", checkRand3(arr, size) ? "" : "in");
    printArr(arr, size);
    printf("Array 2 was filled %scorrecly :\n", checkRand3(arr1, size) ? "" : "in");
    printArr(arr1, size);
    printf("Array 1:\n");
    printf("Max value is %i\nIts index is %i\n", max(arr, size), maxIndex(arr, size));
    printf("Mean value is %f\nThe closest number is at the index %i\n", meanValue(arr, size), meanIndex(arr, size));
    printf("Number %i was find maximum times in our array\n", maxOccurance(arr, size));
    printf("\nArray 2:\n");
    printf("Max value is %i\nIts index is %i\n", max(arr1, size), maxIndex(arr1, size));
    printf("Mean value is %f\nThe closest number is at the index %i\n", meanValue(arr1, size), meanIndex(arr1, size));
    printf("Number %i was find maximum times in our array\n", maxOccurance(arr1, size));
    printf("\nArrays 1 and 2 are %s equal\n", diff(arr, arr1, res, size) ? "" : "not");
    printf("The result if adding Array 1 and Array 2 is :\n");
    add(arr, arr1, res, size);
    printArr(res, size);
    printf("Corresponding elements of Array 1 and Array 2 are %s less or equal\n", lteq(arr, arr1, size) ? "" : "not");
    printf("The result of logical OR to corresponding elements of Array 1 and Array 2:\n");
    lor(arr, arr1, res,size);
    printArr(res, size);
}
void automataTests()
{
    int moves[5] = {18, 18, 208, 5, 208};
    int checkRes[20] = {55, 5, 2};
    int movesLen = sizeof(moves)/sizeof(moves[0]);
    int res[20];
    int resLen = sizeof(res)/sizeof(res[0]);
    int output = run(moves, movesLen, res, resLen);
    puts("These are moves:");
    printArr(moves, movesLen);
    puts("These are results from index 0 to return value:");
    printArr(res, output);
    puts("These are expected results with zeros:");
    printArr(checkRes, resLen);
    printf("Automata is working %scorrectly \n", arrIsEqual(res, checkRes, resLen) ? "" : "in");
    puts("");
    int moves1[5] = {18, 10, 18, 208, 18};
    movesLen = sizeof(moves1)/sizeof(moves1[0]);
    int res1[2] = {0};
    resLen = sizeof(res1)/sizeof(res1[0]);
    int checkRes1[2] = {55, 11};
    output = run(moves1, movesLen, res1, resLen);
    puts("These are moves:");
    printArr(moves1, movesLen);
    puts("These are results from index 0 to return value:");
    printArr(res1, output);
    puts("These are expected results with zeros:");
    printArr(checkRes1, resLen);
    printf("Automata is working %scorrectly\n", arrIsEqual(checkRes1, res1, resLen) ? "" : "in");
}
int arrIsEqual(int arr[], int arr1[], int size)
{
    int i;
    for(i=0; i<size; i++)
        if(arr[i]!=arr1[i])
           return 0;
    return 1;
}
void loopTests()
{
    time_t t;
    srand((unsigned) time(&t));
    printf("Lets get the value of this expression with n=%i, j=%i : %lf\n", rand()%10, rand()%15, calc(rand()%10, rand()%15));
    srand((unsigned) time(&t) + 1);
    printf("Lets get the value of this expression with n=%i, j=%i : %lf\n", rand()%10, rand()%15, calc(rand()%10, rand()%15));
}
main()
{
    automataTests();
}
