#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"

size_t matrix_getsize_1(matrix_t * m)
{
    return m->size_1;
}
size_t matrix_getsize_2(matrix_t * m)
{
    return m->size_2;
}
matrix_t * matrix_new(size_t size_1, size_t size_2, const int arr[size_1][size_2])
{
    matrix_t * out = malloc(sizeof(struct matrix_s));
    size_t size = size_1 * size_2;
    out->size_1 = size_1;
    out->size_2 = size_2;
    out->matrix = malloc(sizeof(int) * size);
    memcpy(out->matrix, arr, sizeof(int) * size);
    return out;
}
matrix_t * matrix_multiply(matrix_t * m1, matrix_t * m2)
{
    if(m1->size_2 != m2->size_1)
        return NULL;

    int multi[m1->size_1][m2->size_2];
    int row_count_1 = m1->size_1;
    int col_count_1 = m1->size_2;
    int col_count_2 = m2->size_2;
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
    return result;
}
matrix_t * matrix_add(matrix_t * m1, matrix_t * m2)
{
    if(m1->size_1 != m2->size_1 || m1->size_2 != m2->size_2)
        return NULL;

    size_t size = m1->size_1 * m1->size_2;
    int add[size];
    for(int i = 0; i < size; i++)
    {
        add[i] = m1->matrix[i] + m2->matrix[i];
    }
    return matrix_new(m1->size_1, m1->size_2, add);

}
void matrix_print(matrix_t * m)
{
    int row_count = m->size_1;
    int col_count = m->size_2;
    for(int m_row = 0; m_row < row_count; m_row++)
    {
        for(int m_column = 0; m_column < col_count; m_column++)
        {
            printf("%4i", m->matrix[m_row * col_count + m_column]);
        }
        puts("");
    }
}
void matrix_free(matrix_t * m)
{
    free(m->matrix);
    free(m);
}
matrix_t * matrix_transpose(matrix_t * m)
{
    size_t rows_count = m->size_1;
    size_t columns_count = m->size_2;
    int temparr[columns_count][rows_count];
    for(size_t i = 0; i < rows_count; i++)
        for(size_t j = 0; j < columns_count; j++)
        {
            temparr[j][i] = m->matrix[i * columns_count + j];
        }
    return matrix_new(columns_count, rows_count, temparr);
}
matrix_t * matrix_multiply_elwise(matrix_t * m1, matrix_t * m2)
{
    if(m1->size_1 != m2->size_1 || m1->size_2 != m2->size_2)
        return NULL;

    size_t size = m1->size_1 * m1->size_2;
    int add[size];
    for(int i = 0; i < size; i++)
    {
        add[i] = m1->matrix[i] * m2->matrix[i];
    }
    return matrix_new(m1->size_1, m1->size_2, add);
}

