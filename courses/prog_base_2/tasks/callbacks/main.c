#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
typedef (*cb)(int, int *);
void loop(int N, int K, int L, cb overCB, int * n_calls_over, cb underCB, int * n_calls_under);
void under(int n, int * n_calls);
void over(int n, int * n_calls);

int main(void)
{
    int n_calls_over, n_calls_under;
    srand(time(NULL));
    loop(10, 6, 3, over, &n_calls_over, under, &n_calls_under);
    puts("Loop Ended");
    printf("Under : %i\nOver : %i\n", n_calls_under, n_calls_over);
    puts("Press anything to end...");
    getch();
    return EXIT_SUCCESS;
}
void loop(int N, int K, int L, cb overCB, int * n_calls_over, cb underCB, int * n_calls_under)
{
    while(!kbhit())
    {
        int randomN = rand()%(2 * (N - 1)) - (N - 1);
        assert(randomN != N);
        assert(randomN != -N);
        if(abs(randomN) < L)
            underCB(randomN, n_calls_under);
        else if(abs(randomN) > K)
            overCB(randomN, n_calls_over);
    }
}
void under(int n, int * n_calls)
{
    (*n_calls)++;
}
void over(int n, int * n_calls)
{
    (*n_calls)++;
}
