#pragma once

/**
 * @file matrix_operations.h
 * @brief Matrix Operations Library
 * 
 * This library provides a set of matrix operations implemented in C. Each function has multiple versions:
 * - The basic version returns a new matrix as the result. ex: m_func()
 * - The 'in-place' version appends 'p' at the end of the function name and modifies the imput matrix. ex: m_funcp()
 * - The 'to' version appends 't' at the end of the function name and writes the result to a provided output matrix. ex: m_funct()
 * 
 * Matrix Initialization:
 * - matrix_init: Initialize a matrix with random values.
 * - matrix_of: Initialize a matrix with a specific value.
 * - matrix_Id: Initialize an identity matrix.
 * - matrix_nId: Initialize a matrix with a scalar multiplied identity matrix.
 * 
 * Matrix Copy:
 * - matrix_copyto: Copy matrix to another (in-place).
 * - matrix_getcpy: Return a deep copy of the matrix.
 * 
 * Matrix Operations:
 * - Various operations for addition, subtraction, scalar addition, scalar subtraction, multiplication, power,
 *   scalar multiplication, scalar division, scalar product, transposition, sum along a direction, multiplication
 *   along a direction, and element-wise function application.
 * 
 * Memory Management:
 * - matrix_free: Free the memory occupied by a matrix.
 * 
 * Note: Please choose the appropriate function based on your specific requirements.
 */


#include <stddef.h>

#define MATRIX_TYPE float

typedef enum{
    ROW,
    COLUMN
}matrix_dir_t;

typedef struct {
    size_t row;
    size_t col;
    MATRIX_TYPE* data;
}matrix_t;

// matrix initialisation with random values
matrix_t* matrix_init(size_t row, size_t col);

// matrix initialisation with x
matrix_t* matrix_of(size_t row, size_t col, MATRIX_TYPE x);

// Id matrix initialisation
matrix_t* matrix_Id(size_t dim);
// n*Id matrix initialisation
matrix_t* matrix_nId(size_t dim, MATRIX_TYPE n);

// getter and setter for element at (i,j)
MATRIX_TYPE matrix_get(const matrix_t *m1, size_t i, size_t j);
void matrix_set(matrix_t *m1, size_t i, size_t j, MATRIX_TYPE val);

// deep copy of matrix
void matrix_copyto(const matrix_t* src, matrix_t* dest);
// return a deep copy of matrix
matrix_t* matrix_getcpy(const matrix_t* src);

// free matrix
void matrix_free(matrix_t *m1);

// matrix addition
matrix_t *m_add(const matrix_t *m1, const matrix_t *m2);
void m_addp(matrix_t *m1, const matrix_t *m2);
void m_addt(const matrix_t *m1, const matrix_t *m2, matrix_t *result);

// matrix scalar addition
matrix_t* m_kadd(const matrix_t *m1, MATRIX_TYPE k);
void m_kaddp(matrix_t *m1, MATRIX_TYPE k);
void m_kaddt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix subtraction
matrix_t *m_sub(const matrix_t *m1, const matrix_t *m2);
void m_subp(matrix_t *m1, const matrix_t *m2);
void m_subt(const matrix_t *m1, const matrix_t *m2, matrix_t *result);

// matrix scalar subtraction
matrix_t* m_ksub(const matrix_t *m1, MATRIX_TYPE k);
void m_ksubp(matrix_t *m1, MATRIX_TYPE k);
void m_ksubt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix multiplication
matrix_t* m_mul(const matrix_t *m1, const matrix_t *m2);
void m_mult(const matrix_t *m1, const matrix_t *m2, matrix_t *result);

// matrix power
matrix_t* m_pow(const matrix_t *m1, size_t n);
void m_powp(matrix_t *m1, size_t n);
void m_powt(const matrix_t *m1, size_t n, matrix_t *result);

// matrix scalar multiplication
matrix_t* m_kmul(const matrix_t *m1, MATRIX_TYPE k);
void m_kmulp(matrix_t *m1, MATRIX_TYPE k);
void m_kmult(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix scalar division
matrix_t* m_kdiv(const matrix_t *m1, MATRIX_TYPE k);
void m_kdivp(matrix_t *m1, MATRIX_TYPE k);
void m_kdivt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix scalar product
MATRIX_TYPE m_dot(const matrix_t *m1, const matrix_t *m2);

// matrix transposition
matrix_t *m_transp(const matrix_t *m1);
void m_transpt(const matrix_t *m1, matrix_t *result);

// matrix sum following a direction
matrix_t *m_sumfd(const matrix_t *m1, matrix_dir_t dir);
void m_sumfdt(const matrix_t *m1, matrix_t *result, matrix_dir_t dir);

// matrix multiplication following a direction
matrix_t *m_mulfd(const matrix_t *m1, matrix_dir_t dir);
void m_mulfdt(const matrix_t *m1, matrix_t *result, matrix_dir_t dir);

// matrix apply function to all elements
matrix_t *m_apply(const matrix_t *m1, MATRIX_TYPE (*f)(MATRIX_TYPE));
void m_applyp(const matrix_t *m1, MATRIX_TYPE (*f)(MATRIX_TYPE));
void m_applyt(const matrix_t *m1, matrix_t *result, MATRIX_TYPE (*f)(MATRIX_TYPE));