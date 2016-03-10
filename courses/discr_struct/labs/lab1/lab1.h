#pragma once
typedef struct matrix_s matrix_t;
matrix_t * lab1_get_paths_at_length(matrix_t * con_mat, int length); // Returns a matrix of paths at certain length
matrix_t * lab1_get_paths(matrix_t * con_mat); // Returns the matrix of paths
matrix_t * lab1_get_reachability(matrix_t * con_mat); // Returns reachability matrix
int lab1_cycles_paths(matrix_t * con_mat, int vertex); // Returns the count of cyles of a specific vertex
matrix_t * lab1_square_diagonal(matrix_t * con_mat); // Returns the square diagonal matrix
