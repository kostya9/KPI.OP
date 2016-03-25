#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "vector.h"

static enum MATRIX_STATUS status = MATRIX_OK;

struct matrix_s{
    size_t rows;
    size_t columns;
    int * matrix;
};
size_t matrix_get_rows_count(matrix_t * m)
{
    return m->rows;
}
size_t matrix_get_columns_count(matrix_t * m)
{
    return m->columns;
}
matrix_t * matrix_new(size_t rows, size_t columns, const int arr[rows][columns])
{
    matrix_t * out = malloc(sizeof(struct matrix_s));
    if(out == NULL)
    {
        status = MATRIX_ERROR_NO_MEMORY;
        return NULL;
    }
    size_t size = rows * columns;
    out->rows = rows;
    out->columns = columns;
    out->matrix = malloc(sizeof(int) * size);
    if(out->matrix == NULL)
    {
        status = MATRIX_ERROR_NO_MEMORY;
        return NULL;
    }
    memcpy(out->matrix, arr, sizeof(int) * size);

    status = MATRIX_OK;
    return out;
}
matrix_t * matrix_multiply(matrix_t * m1, matrix_t * m2)
{
    if(m1 == NULL || m2 == NULL)
    {
        status = MATRIX_ERROR_NO_MEMORY;
        return NULL;
    }
    if(m1->columns != m2->rows)
    {
        status = MATRIX_ERROR_INCORRECT_DIMENSIONS;
        return NULL;
    }

    int multi[m1->rows][m2->columns];
    int row_count_1 = m1->rows;
    int col_count_1 = m1->columns;
    int col_count_2 = m2->columns;
    for(size_t row = 0; row < row_count_1; row++)
        for(size_t column_2 = 0; column_2 < col_count_2 ;column_2++)
        {
            int sum = 0;
            for(size_t column= 0; column < col_count_1; column++)
            {
                sum += m1->matrix[col_count_1 * row  + column] * m2->matrix[col_count_2 * column + column_2];
            }
            multi[row][column_2] = sum;
        }
    matrix_t * result = matrix_new(row_count_1, col_count_2, multi);

    status = MATRIX_OK;
    return result;
}
matrix_t * matrix_add(matrix_t * m1, matrix_t * m2)
{
    if(m1->rows != m2->rows || m1->columns != m2->columns)
    {
        status = MATRIX_ERROR_INCORRECT_DIMENSIONS;
        return NULL;
    }

    size_t size = m1->rows * m1->columns;
    int add[size];
    for(int i = 0; i < size; i++)
    {
        add[i] = m1->matrix[i] + m2->matrix[i];
    }

    status = MATRIX_OK;
    return matrix_new(m1->rows, m1->columns, add);

}
void matrix_print(matrix_t * m)
{
    if(m == NULL)
    {
        status = MATRIX_ERROR_NULL_PTR;
        return;
    }
    int row_count = m->rows;
    int col_count = m->columns;
    for(int m_row = 0; m_row < row_count; m_row++)
    {
        for(int m_column = 0; m_column < col_count; m_column++)
        {
            printf("%4i", m->matrix[m_row * col_count + m_column]);
        }
        puts("");
    }
    status = MATRIX_OK;
}
void matrix_free(matrix_t * m)
{
    if(m == NULL)
    {
        status = MATRIX_ERROR_NULL_PTR;
        return;
    }
    free(m->matrix);
    free(m);
    status = MATRIX_OK;
}
matrix_t * matrix_transpose(matrix_t * m)
{
    if(m == NULL)
    {
        status = MATRIX_ERROR_NULL_PTR;
        return NULL;
    }
    size_t rows_count = m->rows;
    size_t columns_count = m->columns;
    int temparr[columns_count][rows_count];
    for(size_t i = 0; i < rows_count; i++)
        for(size_t j = 0; j < columns_count; j++)
        {
            temparr[j][i] = m->matrix[i * columns_count + j];
        }
    return matrix_new(columns_count, rows_count, temparr); // STATUS IS HERE
}
matrix_t * matrix_multiply_elwise(matrix_t * m1, matrix_t * m2)
{
    if(m1->rows != m2->rows || m1->columns != m2->columns)
    {
        status = MATRIX_ERROR_INCORRECT_DIMENSIONS;
        return NULL;
    }

    size_t size = m1->rows * m1->columns;
    int add[size];
    for(int i = 0; i < size; i++)
    {
        add[i] = m1->matrix[i] * m2->matrix[i];
    }
    return matrix_new(m1->rows, m1->columns, add); // STATUS IS HERE
}
void matrix_set_el(matrix_t * m, int row, int column, int value)
{
    if(m == NULL)
    {
        status = MATRIX_ERROR_NULL_PTR;
        return;
    }
    int row_correct = row < m->rows && row >= 0;
    int column_correct = column < m->columns && column >= 0;
    if(row_correct == 0 || column_correct == 0)
    {
        status = MATRIX_ERROR_INCORRECT_DIMENSIONS;
        return;
    }
    m->matrix[row * m->columns + column] = value;
    status = MATRIX_OK;
}
int matrix_get_el(matrix_t * m, int row, int column)
{
    if(m == NULL)
    {
        status = MATRIX_ERROR_NULL_PTR;
        return;
    }
    int row_correct = row < m->rows && row >= 0;
    int column_correct = column < m->columns && column >= 0;
    if(row_correct == 0 || column_correct == 0)
    {
        status = MATRIX_ERROR_INCORRECT_DIMENSIONS;
        return;
    }
    status = MATRIX_OK;
    return m->matrix[row * m->columns + column];
}
MATRIX_STATUS matrix_get_last_error()
{
    return status;
}
const char * matrix_strstatus(MATRIX_STATUS status)
{
    static const char * strstatus = {"OK", "ERROR_INCORRECT_DIMENSIONS", "ERROR_NULL_PTR", "ERROR_NO_MEMORY"};
    return strstatus[status];
}
matrix_t * matrix_multiply_vector(matrix_t * m, vector_t * vec)
{
    if(m == NULL || vec == NULL)
    {
        status = MATRIX_ERROR_NULL_PTR;
        return NULL;
    }
    if(m->columns != vector_get_size(vec))
    {
        status = MATRIX_ERROR_INCORRECT_DIMENSIONS;
        return NULL;
    }
    int vec_size = vector_get_size(vec);
    int arr[vec_size];
    for(int i = 0; i < vec_size; i++)
    {
        arr[i] = 0;
        for(int j = 0; j < m->columns; j++)
            arr[i] += vector_get_el(vec, j) * matrix_get_el(m, i, j);
    }
    status =  MATRIX_OK;
    return matrix_new(vec_size, 1, arr);
}
