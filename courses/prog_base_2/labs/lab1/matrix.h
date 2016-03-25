#pragma once
#include <stdlib.h>
#include "vector.h"
typedef enum MATRIX_STATUS {MATRIX_OK, MATRIX_ERROR_INCORRECT_DIMENSIONS, MATRIX_ERROR_NULL_PTR, MATRIX_ERROR_NO_MEMORY} MATRIX_STATUS; // ERRORS

typedef struct matrix_s matrix_t; // Type matrix
size_t matrix_get_rows_count(matrix_t *); // Returns the count of rows
size_t matrix_get_columns_count(matrix_t *); // returns the count of columns
void matrix_set_el(matrix_t * m, int row, int column, int value); // Sets an element in the matrix at index(from zero)
int matrix_get_el(matrix_t * m, int row, int column);
//Error handling
MATRIX_STATUS matrix_get_last_error();
const char * matrix_strstatus(MATRIX_STATUS status);


matrix_t * matrix_new(size_t rows, size_t columns, const int arr[rows][columns]); // Creates a new object typed matrix
matrix_t * matrix_multiply(matrix_t * m1, matrix_t * m2); // Multiplies 2 matrices
matrix_t * matrix_multiply_elwise(matrix_t * m1, matrix_t * m2); // Multiplies 2 matrices element-wise
matrix_t * matrix_add(matrix_t * m1, matrix_t * m2); // Adds 2 matrices
matrix_t * matrix_transpose(matrix_t * m); // Returns a transposed matrix
matrix_t * matrix_multiply_vector(matrix_t *, vector_t *);
void matrix_print(matrix_t * m); // Prints the matrix to console
void matrix_free(matrix_t * m); // Frees the memory of type matrix
