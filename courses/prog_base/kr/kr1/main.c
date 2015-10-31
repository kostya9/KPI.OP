#include <stdlib.h>
main()
{	//Uncomment for task5
    //int arr[] = {0, 1, 2, 3, 4, 17, 16, 128, 174};
    //int size = sizeof(arr)/sizeof(arr[0]);
    //Task5(arr, size);

    Task6();
}
void Task5(int arr[],int size)
{
    int i;
    for(i = 0; i < size; i++)
        if(!(arr[i]&(arr[i]-1)) && arr[i]>0)
            printf("%i ", arr[i]);
}
void Task6()
{
	puts("Write your number");
    int input, k, i;
    scanf("%i", &input);
    int arr[2][input];
    for(k = 0; k < 2; k++)
        for(i = 0; i < input; i++)
            arr[k][i] = rand();
    printArr(2, input, arr);
    int arr1[2][input];
//    int arr[input][2];


}
void printArr(int size1, int size2, int arr[size1][size2])
{
    int i, k;
    for(i=0; i<size1; i++)
    {
        for(k=0; k<size2; k++)
            printf("%i ", arr[i][k]);
        puts("");
    }
    puts("");
}
