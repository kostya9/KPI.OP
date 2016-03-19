#include <stdlib.h>
#include <conio.h>
#include <time.h>
typedef (*cb)(int);
void loop(int N, int K, cb overCB, cb underCB);
void under(int L);
void over(int L);

int main(void)
{
    srand(time(NULL));
    loop(10, over, under);
    return EXIT_SUCCESS;
}
void loop(int N, int K, int L, cb overCB, cb underCB)
{
    while(!kbhit())
    {
        int randomN = rand()%(2 * N) - N;
        if(randomN < L)
            underCB(randomN);
        if(randomN > K)
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
