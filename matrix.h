#pragma once

#include <stddef.h>

// we use row-major matrix_t structure

typedef struct {
    size_t row;
    size_t col;
    float *data;
}matrix_t;

//free m1
void freematrix_t(matrix_t *m1);

//Create a matrix_t of 0 with row rows and col columns and return it
matrix_t *matrix(size_t row, size_t col);

//Shuffle m1 and m2 together
void shuffle_matrix_tXY(matrix_t *m1, matrix_t *m2);
void shuffle(matrix_t *m1, matrix_t *m2);

//Create a matrix_t of x with row rows and col columns and return it
matrix_t *matrix_tOf(size_t row, size_t col, float x);

//Print matrix_t m1
void m_print(matrix_t *m1);

//Print name[](m1->row, m1->col)
void m_printSize(char name[], matrix_t *m1);

//Return a copy of m1
matrix_t *m_copy(matrix_t *m1);
void m_copyTo(matrix_t *src, matrix_t *dest);

//Sum m1 and m2 and return the result
matrix_t *m_add(matrix_t *m1, matrix_t *m2);
void m_add_Place(matrix_t *m1, matrix_t *m2);

//Add a column matrix_t m2 to m1 and return the result
matrix_t *m_addColumn(matrix_t *m1, matrix_t *m2);
void m_addColumn_Place(matrix_t *m1, matrix_t *m2);

//Sum all elements of m1 with k and return the result
matrix_t *m_scalarSum(matrix_t *m1, float k);
void m_scalarSum_Place(matrix_t *m1, float k);

//Substract m2 to m1 and return the result
matrix_t *m_sub(matrix_t *m1, matrix_t *m2);
void m_sub_Place(matrix_t *m1, matrix_t *m2);

//Multiply m1 by k and return the result
matrix_t *m_scalarProd(matrix_t *m1, float k);
void m_scalarProd_Place(matrix_t *m1, float k);

//Multiply m1 by m2 and return the result
matrix_t *m_mul(matrix_t *m1, matrix_t *m2);

//Multiply m1 and m2 terms by terms and return the result
matrix_t *m_LineBLineMul(matrix_t *m1, matrix_t *m2);
void m_LineBLine_Place(matrix_t *m1, matrix_t *m2);

//Return the transposed matrix_t of m1
matrix_t *m_transpose(matrix_t *m1);

//Apply function f on all elements of m1 and return the result
matrix_t *m_apply(float (*f)(float), matrix_t *m1);
void m_apply_Place(float (*f)(float), matrix_t *m2);

//Return the column matrix_t containing the sum of all the elements on each line of m1
matrix_t *m_horizontalSum(matrix_t *m1);

//Return the line matrix_t containing the sum of all the elements on each column of m1
matrix_t *m_verticalSum(matrix_t *m1);

//Return the sum of all the elements on each column of m1
float m_sum(matrix_t *m1);