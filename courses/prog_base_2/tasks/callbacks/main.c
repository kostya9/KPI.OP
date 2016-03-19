#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
typedef (*cb)(int);
void loop(int N, int K, int L, cb overCB, cb underCB);
void under(int L);
void over(int L);

int main(void)
{
    srand(time(NULL));
    loop(10, 6, 4, over, under);
    return EXIT_SUCCESS;
}
void loop(int N, int K, int L, cb overCB, cb underCB)
{
    while(!kbhit())
    {
        int randomN = rand()%(2 * (N - 1)) - (N - 1);
        assert(randomN != N);
        assert(randomN != -N);
        if(abs(randomN) < L)
            underCB(randomN);
        if(abs(randomN) > K)
            overCB(randomN);
    }
}
void under(int L)
{
    static int n_calls;
    n_calls++;
}
void over(int L)
{
    static int n_calls;
    n_calls++;
}
