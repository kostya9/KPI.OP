#pragma once
#include <stdlib.h>

struct matrix_s{
    size_t size_1;
    size_t size_2;
    int * matrix;
};
typedef struct matrix_s matrix_t; // Type matrix
size_t matrix_getsize_1(matrix_t *); // Returns the count of rows
size_t matrix_getsize_2(matrix_t *); // returns the count of columns
matrix_t * matrix_new(size_t size_1, size_t size_2, const int arr[size_1][size_2]); // Creates a new object typed matrix
matrix_t * matrix_multiply(matrix_t * m1, matrix_t * m2); // Multiplies 2 matrices
matrix_t * matrix_multiply_elwise(matrix_t * m1, matrix_t * m2); // Multiplies 2 matrices elementwise
matrix_t * matrix_add(matrix_t * m1, matrix_t * m2); // Adds 2 matrices
matrix_t * matrix_transpose(matrix_t * m); // Returns a transposed matrix
void matrix_print(matrix_t * m); // Prints the matrix to console
void matrix_free(matrix_t * m); // Frees the memory of type matrix
