#pragma once

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
matrix_t* matrix_Id(size_t row, size_t col);
// n*Id matrix initialisation
matrix_t* matrix_nId(size_t row, size_t col, MATRIX_TYPE n);

// deep copy of matrix (secure and unsecure)
void matrix_copyto(matrix_t* dest, const matrix_t* src);
void matrix_copytos(matrix_t* dest, const matrix_t* src);
// return a deep copy of matrix
matrix_t* matrix_getcpy(const matrix_t* src);

// free matrix
void matrix_free(matrix_t *m1);

// matrix addition
matrix_t *m_add(const matrix_t *m1, const matrix_t *m2);
void m_addp(matrix_t *m1, const matrix_t *m2);
void m_addt(const matrix_t *m1, const matrix_t *m2, matrix_t *result);
void m_addts(const matrix_t *m1, const matrix_t *m2, matrix_t *result);

// matrix scalar addition
matrix_t* m_kadd(const matrix_t *m1, MATRIX_TYPE k);
void m_kaddp(matrix_t *m1, MATRIX_TYPE k);
void m_kaddt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);
void m_kaddts(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix subtraction
matrix_t *m_sub(const matrix_t *m1, const matrix_t *m2);
void m_subp(matrix_t *m1, const matrix_t *m2);
void m_subt(const matrix_t *m1, const matrix_t *m2, matrix_t *result);
void m_subts(const matrix_t *m1, const matrix_t *m2, matrix_t *result);

// matrix scalar subtraction
matrix_t* m_ksub(const matrix_t *m1, MATRIX_TYPE k);
void m_ksubp(matrix_t *m1, MATRIX_TYPE k);
void m_ksubt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);
void m_ksubts(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix multiplication
matrix_t* m_mul(const matrix_t *m1, const matrix_t *m2);
void m_mult(const matrix_t *m1, const matrix_t *m2, matrix_t *result);
void m_mults(const matrix_t *m1, const matrix_t *m2, matrix_t *result);

// matrix power
matrix_t* m_pow(const matrix_t *m1, size_t n);

// matrix scalar multiplication
matrix_t* m_kmul(const matrix_t *m1, MATRIX_TYPE k);
void m_kmulp(matrix_t *m1, MATRIX_TYPE k);
void m_kmult(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);
void m_kmults(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix scalar division
matrix_t* m_kdiv(const matrix_t *m1, MATRIX_TYPE k);
void m_kdivp(matrix_t *m1, MATRIX_TYPE k);
void m_kdivt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);
void m_kdivts(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result);

// matrix scalar product
MATRIX_TYPE *m_dot(const matrix_t *m1, const matrix_t *m2);

// matrix transposition
matrix_t *m_transp(const matrix_t *m1);
void m_transpt(const matrix_t *m1, matrix_t *result);
void m_transpts(const matrix_t *m1, matrix_t *result);

// matrix sum following a direction
matrix_t *m_sumfd(const matrix_t *m1, matrix_dir_t dir);
void m_sumfdt(const matrix_t *m1, matrix_t *result, matrix_dir_t dir);
void m_sumfdts(const matrix_t *m1, matrix_t *result, matrix_dir_t dir);

// matrix multiplication following a direction
matrix_t *m_mulfd(const matrix_t *m1, matrix_dir_t dir);
void m_mulfdt(const matrix_t *m1, matrix_t *result, matrix_dir_t dir);
void m_mulfdts(const matrix_t *m1, matrix_t *result, matrix_dir_t dir);

// matrix apply function to all elements
matrix_t *m_apply(const matrix_t *m1, MATRIX_TYPE (*f)(MATRIX_TYPE));
void m_applyp(const matrix_t *m1, MATRIX_TYPE (*f)(MATRIX_TYPE));
void m_applyt(const matrix_t *m1, matrix_t *result, MATRIX_TYPE (*f)(MATRIX_TYPE));
void m_applyts(const matrix_t *m1, matrix_t *result, MATRIX_TYPE (*f)(MATRIX_TYPE));