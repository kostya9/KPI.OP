#pragma once
typedef struct matrix_s matrix_t;
matrix_t * lab1_get_paths_at_length(matrix_t * con_mat, int length);
matrix_t * lab1_get_connections(matrix_t * con_mat);
int lab1_cycles_paths(matrix_t * con_mat, int vertex);
