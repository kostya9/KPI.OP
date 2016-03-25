#include <stdio.h>
#include <stdlib.h>
void matrix_test();
void vector_test();
void print_fancylines() // A useless thingy
{
    const int LINES = 1;
    const int COUNT = 100;
    for(int j = 0; j < LINES; j++)
    {
        for(int i = 0; i < COUNT; i++)
            putc('-', stdout);
        puts("");
    }
}
int main(void)
{
    print_fancylines();
    puts("Testing matrices...");
    print_fancylines();
    matrix_test();
    print_fancylines();
    puts("Testing vectors...");
    print_fancylines();
    vector_test();
    return EXIT_SUCCESS;
}
