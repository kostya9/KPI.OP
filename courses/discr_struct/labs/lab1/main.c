#include "lab1.h"
#include "matrix.h"
int main(void)
{
    const int IDENTITY_3_3[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    int con_arr[] = {0, 1, 0, 0, 0,    1, 0, 1, 0, 0,  0, 0,0, 1, 0,   0, 1, 0, 0, 1,  0, 0, 0, 1, 0};
    matrix_t * con_mat = matrix_new(5, 5, con_arr);
    matrix_t * m_new = lab1_get_connections(con_mat);
    matrix_print(m_new);
    matrix_free(m_new);
    matrix_free(con_mat);



}
