#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
typedef (*cb)(int, int *);
void loop(int N, int K, int L, cb overCB, int * n_calls_over, cb underCB, int * n_calls_under);
void under(int n, int * n_calls);
void undertwo(int n, int * n_calls);
void over(int n, int * n_calls);
void overtwo(int n, int * n_calls);

int main(void)
{
    int n_calls_over, n_calls_under;
    srand(time(NULL));
    puts("Press anything to break...");
    loop(10, 6, 3, over, &n_calls_over, under, &n_calls_under);
    puts("Loop with correct callbacks ended.");
    printf("Under : %i\nOver : %i\n", n_calls_under, n_calls_over);
    puts("Press anything to continue...");
    puts("");
    puts("Press anything to break...");
    loop(10, 6, 3, overtwo, &n_calls_over, undertwo, &n_calls_under);
    puts("Loop with incorrect(even n_of_calls) callbacks ended.");
    printf("Under : %i\nOver : %i\n", n_calls_under, n_calls_over);
    puts("Press anything to quit...");
    getch();
    return EXIT_SUCCESS;
}
void loop(int N, int K, int L, cb overCB, int * n_calls_over, cb underCB, int * n_calls_under)
{
    *n_calls_over = 0;
    *n_calls_under = 0;
    while(kbhit() == 0)
    {
        int randomN = rand()%(2 * (N - 1)) - (N - 1);
        assert(randomN != N);
        assert(randomN != -N);
        if(abs(randomN) < L && underCB != NULL)
            underCB(randomN, n_calls_under);
        else if(abs(randomN) > K && overCB != NULL)
            overCB(randomN, n_calls_over);
    }
    getch();
}
void under(int n, int * n_calls)
{
    (*n_calls)++;
}
void undertwo(int n, int * n_calls)
{
    (*n_calls)+=2;
}
void over(int n, int * n_calls)
{
    (*n_calls)++;
}
void overtwo(int n, int * n_calls)
{
    (*n_calls)+=2;
}
