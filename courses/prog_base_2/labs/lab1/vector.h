#pragma once
#include "matrix.h"
typedef struct vector_s vector_t;
typedef enum VECTOR_STATUS {VECTOR_OK, VECTOR_ERROR_INCORRECT_DIMENSIONS, VECTOR_ERROR_NULL_PTR, VECTOR_ERROR_NO_MEMORY} VECTOR_STATUS;
vector_t * vector_new(int size, const int values[]); // COLUMN VECTOR
void vector_set_el(vector_t * vec, int index, int value);
int vector_get_el(vector_t * vec, int index);
int vector_get_size(vector_t * vec);

vector_t * vector_multiply_vector(vector_t * vec1, vector_t * vec2); // ELEMENTWISE
void vector_free(vector_t * vec);
