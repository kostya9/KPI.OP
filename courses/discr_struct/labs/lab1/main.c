#include <stdio.h>
#include "lab1.h"
#include "matrix.h"
int main(void)
{
    int con_arr[] = {0, 1, 0, 0, 0,    1, 0, 1, 0, 0,  0, 0,0, 1, 0,   0, 1, 0, 0, 1,  0, 0, 0, 1, 0};
    matrix_t * con_mat = matrix_new(5, 5, con_arr);
    puts("A matrix:");
    matrix_print(con_mat);
    matrix_t * reach_mat = lab1_get_reachability(con_mat);
    int vertex = 4;
    int vertex_cycles = lab1_cycles_paths(con_mat, vertex);
    puts("R matrix : ");
    matrix_print(reach_mat);

    puts("D matrix : ");
    matrix_t * paths_mat = lab1_get_paths(con_mat);
    matrix_print(paths_mat);

    printf("There are %i cycles to v%i\n", vertex_cycles, vertex);
    puts("Square-diagonal:");
    matrix_t * sq_dia = lab1_square_diagonal(con_mat);
    matrix_print(sq_dia);
    matrix_free(sq_dia);
    matrix_free(reach_mat);
    matrix_free(con_mat);
    matrix_free(paths_mat);



}
