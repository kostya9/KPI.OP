#include "matrix.h"
#include "vector.h"
static VECTOR_STATUS status = VECTOR_OK;

struct vector_s
{
    matrix_t * mat; // COLUMN MATRIX, COLUMNS = 1
};

vector_t * vector_new(int size, const int values[])
{
    matrix_t * m = matrix_new(size, 1, values);
    vector_t * vec = malloc(sizeof(struct vector_s));
    if(vec == NULL || m == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    vec->mat = m;
    status = VECTOR_OK;
    return vec;
}
void vector_set_el(vector_t * vec, int index, int value)
{
    if(vec == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    if(index < 0 || index >= vector_get_size(vec))
    {
        status = VECTOR_ERROR_INCORRECT_DIMENSIONS;
        return;
    }
    status = VECTOR_OK;
    matrix_set_el(vec->mat, index, 0, value);
}
int vector_get_el(vector_t * vec, int index)
{
    if(vec == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    if(index < 0 || index >= vector_get_size(vec))
    {
        status = VECTOR_ERROR_INCORRECT_DIMENSIONS;
        return 0;
    }
    status = VECTOR_OK;
    return matrix_get_el(vec->mat, index, 0);
}
int vector_get_size(vector_t * vec)
{
    if(vec == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    status = VECTOR_OK;
    return matrix_get_rows_count(vec->mat);
}
vector_t * vector_multiply_vector(vector_t * vec1, vector_t * vec2)
{
    if(vec1 == NULL || vec2 == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    if(vector_get_size(vec1) != vector_get_size(vec2))
    {
        status = VECTOR_ERROR_INCORRECT_DIMENSIONS;
        return NULL;
    }
    vector_t * vec = malloc(sizeof(struct vector_s));
    if(vec == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    vec->mat = matrix_multiply_elwise(vec1->mat, vec2->mat);
    if(vec->mat == NULL)
    {
        status = VECTOR_ERROR_NO_MEMORY;
        return NULL;
    }
    status = VECTOR_OK;
    return vec;
}
void vector_free(vector_t * vec)
{
    if(vec == NULL)
    {
        status = VECTOR_ERROR_NULL_PTR;
        return;
    }
    matrix_free(vec->mat);
    free(vec);
    status = VECTOR_OK;
}
VECTOR_STATUS vector_get_last_error()
{
    return status;
}
const char * vector_strstatus(VECTOR_STATUS status)
{
    static const char * strstatus = {"OK", "ERROR_INCORRECT_DIMENSIONS", "ERROR_NULL_PTR", "ERROR_NO_MEMORY"};
    return strstatus[status];
}
