#include <stdlib.h>
#include <err.h>

#include "matrix.h"
#include "state.h"

matrix_t* matrix_init(size_t row, size_t col){
    /*
        * matrix initialisation with random values
        * @params row: number of rows
        *        col: number of columns
        * @return matrix_t* : pointer to the matrix
    */
    matrix_t *result = malloc(sizeof(matrix_t));
    result->row = row;
    result->col = col;
    result->data = calloc(result->row * result->col, sizeof(MATRIX_TYPE));
    if (!result->data) {
        matrix_free(result);
        return NULL;
    }

    return result;
}

matrix_t* matrix_of(size_t row, size_t col, MATRIX_TYPE x){
    /*
        * matrix initialisation with x
        * @params row: number of rows
        *         col: number of columns
        *         x: value of each element
        * @return matrix_t* : pointer to the matrix
    */
    matrix_t *result;
    if(!(result = matrix_init(row, col)))
        return NULL;

    for(size_t i = 0; i < result->row * result->col; i++)
        result->data[i] = x;
    return result;
}

MATRIX_TYPE matrix_get(const matrix_t *m1, size_t i, size_t j){
    /*
        * getter for element at (i,j)
        * @params m1: pointer to the matrix
        *         i: row index
        *         j: column index
        * @return MATRIX_TYPE : value of the element
    */
    return m1->data[i*m1->col + j];
}

void matrix_set(matrix_t *m1, size_t i, size_t j, MATRIX_TYPE val){
    /*
        * setter for element at (i,j)
        * @params m1: pointer to the matrix
        *         i: row index
        *         j: column index
        *         val: value to set
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "matrix_set: %s", MATRIX_NULL_POINTER_MESSAGE);

    if (i >= m1->row || j >= m1->col)
        errx(MATRIX_INDEX_OUT_OF_BOUNDS, "matrix_set: %s", MATRIX_INDEX_OUT_OF_BOUNDS_MESSAGE);

    m1->data[i*m1->col + j] = val;
}

matrix_t* matrix_Id(size_t dim){
    /*
        * Id matrix initialisation
        * @params dim: dimension of the matrix
        * @return matrix_t* : pointer to the matrix
    */
    matrix_t *result;
    if(!(result = matrix_init(dim, dim)))
        return NULL;
    
    for(size_t i = 0; i < result->row; i++)
        matrix_set(result, i, i, 1);
    return result;
}

matrix_t* matrix_nId(size_t dim, MATRIX_TYPE n){
    /*
        * n*Id matrix initialisation
        * @params row: number of rows
        *         col: number of columns
        *         n: value of each element
        * @return matrix_t* : pointer to the matrix
    */
    matrix_t *result;
    if(!(result = matrix_init(dim, dim)))
        return NULL;

    for(size_t i = 0; i < result->row; i++)
        matrix_set(result, i, i, n);
    return result;
}

void matrix_copyto(const matrix_t* src, matrix_t* dest){
    /*
        * deep copy of matrix
        * @params dest: pointer to the destination matrix
        *         src: pointer to the source matrix
    */
    if(!dest || !src)
        errx(MATRIX_NULL_POINTER, "matrix_copyto: %s", MATRIX_NULL_POINTER_MESSAGE);

    if(dest->col != src->col || dest->row != src->row)
        errx(MATRIX_INVALID_DIMENSIONS, "matrix_copyto: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);

    for(size_t i = 0; i < src->row * src->col; i++)
        dest->data[i] = src->data[i];
}

matrix_t* matrix_getcpy(const matrix_t* src){
    /*
        * return a deep copy of matrix
        * @params src: pointer to the source matrix
        * @return matrix_t* : pointer to the copy of the matrix
    */
    if(!src)
        errx(MATRIX_NULL_POINTER, "matrix_getcpy: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result = matrix_init(src->row, src->col);
    matrix_copyto(src, result);
    return result;
}

void matrix_free(matrix_t *m1){
    /*
        * free matrix
        * @params m1: pointer to the matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "matrix_free: %s", MATRIX_NULL_POINTER_MESSAGE);
    free(m1->data);
    free(m1);
}

matrix_t *m_add(const matrix_t *m1, const matrix_t *m2){
    /*
        * matrix addition
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1 || !m2)
        errx(MATRIX_NULL_POINTER, "m_add: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m2->row || m1->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_add: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->row, m1->col)))
        return NULL;

    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] + m2->data[i];

    return result;
}

void m_addp(matrix_t *m1, const matrix_t *m2){
    /*
        * in place matrix addition
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
    */
    if(!m1 || !m2)
        errx(MATRIX_NULL_POINTER, "m_addp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m2->row || m1->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_addp: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        m1->data[i] += m2->data[i];
}

void m_addt(const matrix_t *m1, const matrix_t *m2, matrix_t *result){
    /*
        * matrix addition to result
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        *         result: pointer to the result matrix
    */
    if(!m1 || !m2 || !result)
        errx(MATRIX_NULL_POINTER, "m_addt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m2->row || m1->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_addt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    if(result->row != m1->row || result->col != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_addt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] + m2->data[i];
}

matrix_t* m_kadd(const matrix_t *m1, MATRIX_TYPE k){
    /*
        * matrix scalar addition
        * @params m1: pointer to the matrix
        *         k: scalar value
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_kadd: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->row, m1->col)))
        return NULL;

    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] + k;

    return result;
}

void m_kaddp(matrix_t *m1, MATRIX_TYPE k){
    /*
        * in place matrix scalar addition
        * @params m1: pointer to the matrix
        *         k: scalar value
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_kaddp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        m1->data[i] += k;
}

void m_kaddt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result){
    /*
        * matrix scalar addition to result
        * @params m1: pointer to the matrix
        *         k: scalar value
        *         result: pointer to the result matrix
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_kaddt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(result->row != m1->row || result->col != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_kaddt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] + k;
}

matrix_t *m_sub(const matrix_t *m1, const matrix_t *m2){
    /*
        * matrix subtraction
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1 || !m2)
        errx(MATRIX_NULL_POINTER, "m_sub: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m2->row || m1->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_sub: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->row, m1->col)))
        return NULL;

    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] - m2->data[i];

    return result;

}

void m_subp(matrix_t *m1, const matrix_t *m2){
    /*
        * in place matrix subtraction
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
    */
    if(!m1 || !m2)
        errx(MATRIX_NULL_POINTER, "m_subp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m2->row || m1->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_subp: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        m1->data[i] -= m2->data[i];
}

void m_subt(const matrix_t *m1, const matrix_t *m2, matrix_t *result){
    /*
        * matrix subtraction to result
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        *         result: pointer to the result matrix
    */
    if(!m1 || !m2 || !result)
        errx(MATRIX_NULL_POINTER, "m_subt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m2->row || m1->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_subt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    if(result->row != m1->row || result->col != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_subt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] - m2->data[i];
}

matrix_t* m_ksub(const matrix_t *m1, MATRIX_TYPE k){
    /*
        * matrix scalar subtraction
        * @params m1: pointer to the matrix
        *         k: scalar value
        * @return matrix_t* : pointer to the result matrix
    */
    return m_kadd(m1, -k);
}

void m_ksubp(matrix_t *m1, MATRIX_TYPE k){
    /*
        * in place matrix scalar subtraction
        * @params m1: pointer to the matrix
        *         k: scalar value
    */
    return m_kaddp(m1, -k);
}

void m_ksubt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result){
    /*
        * matrix scalar subtraction to result
        * @params m1: pointer to the matrix
        *         k: scalar value
        *         result: pointer to the result matrix
    */
    return m_kaddt(m1, -k, result);
}

matrix_t* m_mul(const matrix_t *m1, const matrix_t *m2){
    /*
        * matrix multiplication
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1 || !m2)
        errx(MATRIX_NULL_POINTER, "m_mul: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->col != m2->row)
        errx(MATRIX_INVALID_DIMENSIONS, "m_mul: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->row, m2->col)))
        return NULL;

    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m2->col; j++)
            for(size_t k = 0; k < m1->col; k++)
                result->data[i*result->col + j] += m1->data[i*m1->col + k] * m2->data[k*m2->col + j];

    return result;
}

void m_mult(const matrix_t *m1, const matrix_t *m2, matrix_t *result){
    /*
        * matrix multiplication to result
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        *         result: pointer to the result matrix
    */
    if(!m1 || !m2 || !result)
        errx(MATRIX_NULL_POINTER, "m_mult: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->col != m2->row)
        errx(MATRIX_INVALID_DIMENSIONS, "m_mult: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    if(result->row != m1->row || result->col != m2->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_mult: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m2->col; j++)
            for(size_t k = 0; k < m1->col; k++)
                result->data[i*result->col + j] += m1->data[i*m1->col + k] * m2->data[k*m2->col + j];
}

matrix_t* m_pow(const matrix_t *m1, size_t n){
    /*
        * matrix power
        * @params m1: pointer to the matrix
        *         n: power
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_pow: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_pow: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_Id(m1->row)))
        return NULL;

    matrix_t *tmp;
    if(!(tmp = matrix_getcpy(m1)))
        return NULL;

    for(size_t i = 0; i < n; i++){
        m_mult(result, tmp, result);
        matrix_free(tmp);
        tmp = matrix_getcpy(result);
    }

    matrix_free(tmp);
    return result;
}

void m_powp(matrix_t *m1, size_t n){
    /*
        * in place matrix power
        * @params m1: pointer to the matrix
        *         n: power
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_powp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_powp: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_Id(m1->row)))
        return;

    matrix_t *tmp;
    if(!(tmp = matrix_getcpy(m1))){
        matrix_free(result);
        return;
    }

    for(size_t i = 0; i < n; i++){
        m_mult(result, tmp, result);
        matrix_free(tmp);
        tmp = matrix_getcpy(result);
    }

    matrix_free(tmp);
    matrix_copyto(result, m1);
    matrix_free(result);
}

void m_powt(const matrix_t *m1, size_t n, matrix_t *result){
    /*
        * matrix power to result
        * @params m1: pointer to the matrix
        *         n: power
        *         result: pointer to the result matrix
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_powt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_powt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    if(result->row != m1->row || result->col != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_powt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    matrix_t *tmp;
    if(!(tmp = matrix_getcpy(m1)))
        return;

    for(size_t i = 0; i < n; i++){
        m_mult(result, tmp, result);
        matrix_copyto(result, tmp);
    }

    matrix_free(tmp);
}

matrix_t* m_kmul(const matrix_t *m1, MATRIX_TYPE k){
    /*
        * matrix scalar multiplication
        * @params m1: pointer to the matrix
        *         k: scalar value
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_kmul: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->row, m1->col)))
        return NULL;

    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] * k;

    return result;
}

void m_kmulp(matrix_t *m1, MATRIX_TYPE k){
    /*
        * in place matrix scalar multiplication
        * @params m1: pointer to the matrix
        *         k: scalar value
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_kmulp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        m1->data[i] *= k;
}

void m_kmult(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result){
    /*
        * matrix scalar multiplication to result
        * @params m1: pointer to the matrix
        *         k: scalar value
        *         result: pointer to the result matrix
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_kmult: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(result->row != m1->row || result->col != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_kmult: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = m1->data[i] * k;
}

// matrix scalar division
matrix_t* m_kdiv(const matrix_t *m1, MATRIX_TYPE k){
    /*
        * matrix scalar division
        * @params m1: pointer to the matrix
        *         k: scalar value
        * @return matrix_t* : pointer to the result matrix
    */
    return m_kmul(m1, 1/k);
}

void m_kdivp(matrix_t *m1, MATRIX_TYPE k){
    /*
        * in place matrix scalar division
        * @params m1: pointer to the matrix
        *         k: scalar value
    */
    return m_kmulp(m1, 1/k);
}

void m_kdivt(const matrix_t *m1, MATRIX_TYPE k, matrix_t *result){
    /*
        * matrix scalar division to result
        * @params m1: pointer to the matrix
        *         k: scalar value
        *         result: pointer to the result matrix
    */
    return m_kmult(m1, 1/k, result);
}

// matrix scalar product
MATRIX_TYPE m_dot(const matrix_t *m1, const matrix_t *m2){
    /*
        * matrix scalar product
        * m1 and m2 must be vectors (row or column)
        * @params m1: pointer to the first matrix
        *         m2: pointer to the second matrix
        * @return MATRIX_TYPE* : pointer to the result scalar
    */
    if(!m1 || !m2)
        errx(MATRIX_NULL_POINTER, "m_dot: %s", MATRIX_NULL_POINTER_MESSAGE);

    // if matrices are not vectors
    if(m1->row != 1 && m1->col != 1 || m2->row != 1 && m2->col != 1)
        errx(MATRIX_INVALID_DIMENSIONS, "m_dot: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);

    // if matrices dimensions are not compatibles
    if(m1->row == 1){
        if(m2->row == 1){
            if(m1->col != m2->col)
                errx(MATRIX_INVALID_DIMENSIONS, "m_dot: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
        }else if(m1->col != m2->row)
            errx(MATRIX_INVALID_DIMENSIONS, "m_dot: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    }else{
        if(m2->col == 1){
            if(m1->row != m2->row)
                errx(MATRIX_INVALID_DIMENSIONS, "m_dot: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
        }else if(m1->row != m2->col)
            errx(MATRIX_INVALID_DIMENSIONS, "m_dot: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    }
    
    MATRIX_TYPE result = 0;
    for(size_t i = 0; i < m1->row * m1->col; i++)
        result += m1->data[i] * m2->data[i];

    return result;
}

matrix_t *m_transp(const matrix_t *m1){
    /*
        * matrix transposition
        * @params m1: pointer to the matrix
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_transp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->col, m1->row)))
        return NULL;

    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m1->col; j++)
            result->data[j*result->col + i] = m1->data[i*m1->col + j];

    return result;
}

void m_transpt(const matrix_t *m1, matrix_t *result){
    /*
        * matrix transposition to result
        * @params m1: pointer to the matrix
        *         result: pointer to the result matrix
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_transpt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(m1->row != result->col || m1->col != result->row)
        errx(MATRIX_INVALID_DIMENSIONS, "m_transpt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);

    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m1->col; j++)
            result->data[j*result->col + i] = m1->data[i*m1->col + j];
}

matrix_t *m_sumfd(const matrix_t *m1, matrix_dir_t dir){
    /*
        * matrix sum following a direction
        * @params m1: pointer to the matrix
        *         dir: direction
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_sumfd: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result;
    if(dir == ROW)
        result = matrix_of(1, m1->col, 0);
    else
        result = matrix_of(m1->row, 1, 0);

    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m1->col; j++)
            if(dir == ROW)
                result->data[j] += m1->data[i*m1->col + j];
            else
                result->data[i] += m1->data[i*m1->col + j];

    return result;
}

void m_sumfdt(const matrix_t *m1, matrix_t *result, matrix_dir_t dir){
    /*
        * matrix sum following a direction to result
        * @params m1: pointer to the matrix
        *         result: pointer to the result matrix
        *         dir: direction
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_sumfdt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(dir == ROW){
        if(result->row != 1 || result->col != m1->col)
            errx(MATRIX_INVALID_DIMENSIONS, "m_sumfdt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    }else{
        if(result->row != m1->row || result->col != 1)
            errx(MATRIX_INVALID_DIMENSIONS, "m_sumfdt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    }

    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m1->col; j++)
            if(dir == ROW)
                result->data[j] += m1->data[i*m1->col + j];
            else
                result->data[i] += m1->data[i*m1->col + j];
}

matrix_t *m_mulfd(const matrix_t *m1, matrix_dir_t dir){
    /*
        * matrix multiplication following a direction
        * @params m1: pointer to the matrix
        *         dir: direction
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_mulfd: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result;
    if(dir == ROW)
        result = matrix_of(1, m1->col, 1);
    else
        result = matrix_of(m1->row, 1, 1);

    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m1->col; j++)
            if(dir == ROW)
                result->data[j] *= m1->data[i*m1->col + j];
            else
                result->data[i] *= m1->data[i*m1->col + j];

    return result;
}

void m_mulfdt(const matrix_t *m1, matrix_t *result, matrix_dir_t dir){
    /*
        * matrix multiplication following a direction to result
        * @params m1: pointer to the matrix
        *         result: pointer to the result matrix
        *         dir: direction
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_mulfdt: %s", MATRIX_NULL_POINTER_MESSAGE);

    if(dir == ROW){
        if(result->row != 1 || result->col != m1->col)
            errx(MATRIX_INVALID_DIMENSIONS, "m_sumfdt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    }else{
        if(result->row != m1->row || result->col != 1)
            errx(MATRIX_INVALID_DIMENSIONS, "m_sumfdt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    }
    
    for(size_t i = 0; i < m1->row; i++)
        for(size_t j = 0; j < m1->col; j++)
            if(dir == ROW)
                result->data[j] *= m1->data[i*m1->col + j];
            else
                result->data[i] *= m1->data[i*m1->col + j];
}

matrix_t *m_apply(const matrix_t *m1, MATRIX_TYPE (*f)(MATRIX_TYPE)){
    /*
        * apply a function to each element of the matrix
        * @params m1: pointer to the matrix
        *         f: function to apply
        * @return matrix_t* : pointer to the result matrix
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_apply: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    matrix_t *result;
    if(!(result = matrix_init(m1->row, m1->col)))
        return NULL;

    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = f(m1->data[i]);

    return result;
}

void m_applyp(const matrix_t *m1, MATRIX_TYPE (*f)(MATRIX_TYPE)){
    /*
        * apply a function to each element of the matrix
        * @params m1: pointer to the matrix
        *         f: function to apply
    */
    if(!m1)
        errx(MATRIX_NULL_POINTER, "m_applyp: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        m1->data[i] = f(m1->data[i]);
}

void m_applyt(const matrix_t *m1, matrix_t *result, MATRIX_TYPE (*f)(MATRIX_TYPE)){
    /*
        * apply a function to each element of the matrix to result
        * @params m1: pointer to the matrix
        *         result: pointer to the result matrix
        *         f: function to apply
    */
    if(!m1 || !result)
        errx(MATRIX_NULL_POINTER, "m_applyt: %s", MATRIX_NULL_POINTER_MESSAGE);
    
    if(result->row != m1->row || result->col != m1->col)
        errx(MATRIX_INVALID_DIMENSIONS, "m_applyt: %s", MATRIX_INVALID_DIMENSIONS_MESSAGE);
    
    for(size_t i = 0; i < m1->row * m1->col; i++)
        result->data[i] = f(m1->data[i]);
}