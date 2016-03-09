#pragma once
#include <stdlib.h>

struct matrix_s{
    size_t size_1;
    size_t size_2;
    int * matrix;
};
typedef struct matrix_s matrix_t;
size_t matrix_getsize_1(matrix_t *);
size_t matrix_getsize_2(matrix_t *);
matrix_t * matrix_new(size_t size_1, size_t size_2, const int arr[size_1][size_2]);
matrix_t * matrix_multiply(matrix_t * m1, matrix_t * m2);
matrix_t * matrix_add(matrix_t * m1, matrix_t * m2);
void matrix_print(matrix_t * m);
void matrix_free(matrix_t * m);
