#include <stdio.h>
#include "lab1.h"
#include "matrix.h"
int main(void)
{
    const int IDENTITY_3_3[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    int con_arr[] = {0, 1, 0, 0, 0,    1, 0, 1, 0, 0,  0, 0,0, 1, 0,   0, 1, 0, 0, 1,  0, 0, 0, 1, 0};
    matrix_t * con_mat = matrix_new(5, 5, con_arr);
    matrix_t * m_new = lab1_get_connections(con_mat);
    int vertex = 4;
    int vertex_cycles = lab1_cycles_paths(con_mat, vertex);
    matrix_print(m_new);
    printf("There are %i cycles to v%i", vertex_cycles, vertex);
    matrix_free(m_new);
    matrix_free(con_mat);



}
