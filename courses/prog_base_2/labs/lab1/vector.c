#include "matrix.h"
#include "vector.h"

struct vector_s
{
    matrix_t * mat; // COLUMN MATRIX, COLUMNS = 1
};

vector_t * vector_new(int size, const int values[])
{
    matrix_t * m = matrix_new(size, 1, values);
    vector_t * vec = malloc(sizeof(struct vector_s));
    vec->mat = m;
    return vec;
}
void vector_set_el(vector_t * vec, int index, int value)
{
    matrix_set_el(vec->mat, index, 0, value);
}
int vector_get_el(vector_t * vec, int index)
{
    return matrix_get_el(vec->mat, index, 0);
}
int vector_get_size(vector_t * vec)
{
    return matrix_get_rows_count(vec->mat);
}
vector_t * vector_multiply_vector(vector_t * vec1, vector_t * vec2)
{
    vector_t * vec = malloc(sizeof(struct vector_s));
    vec->mat = matrix_multiply_elwise(vec1->mat, vec2->mat);
    return vec;
}
void vector_free(vector_t * vec)
{
    matrix_free(vec->mat);
    free(vec);
}
