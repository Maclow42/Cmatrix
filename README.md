# Matrix Operations Library

This C library provides a comprehensive set of matrix operations. It is designed with flexibility in mind, offering various versions of each function to suit different use cases.

## Matrix Initialization

- **matrix_init**: Initialize a matrix with random values.
- **matrix_of**: Initialize a matrix with a specific value.
- **matrix_Id**: Initialize an identity matrix.
- **matrix_nId**: Initialize a matrix with a scalar-multiplied identity matrix.

## Matrix Copy

- **matrix_copyto**: Copy matrix to another (in-place).
- **matrix_getcpy**: Return a deep copy of the matrix.

## Matrix Operations

### Addition

- **m_add**: Returns a new matrix as the result of addition.
- **m_addp**: In-place addition, modifies the input matrix.
- **m_addt**: Addition with the result written to a provided output matrix.

### Scalar Addition

- **m_kadd**: Returns a new matrix with scalar addition.
- **m_kaddp**: In-place scalar addition.
- **m_kaddt**: Scalar addition with the result written to a provided output matrix.

### Subtraction

- **m_sub**: Returns a new matrix as the result of subtraction.
- **m_subp**: In-place subtraction, modifies the input matrix.
- **m_subt**: Subtraction with the result written to a provided output matrix.

### Scalar Subtraction

- **m_ksub**: Returns a new matrix with scalar subtraction.
- **m_ksubp**: In-place scalar subtraction.
- **m_ksubt**: Scalar subtraction with the result written to a provided output matrix.

### Multiplication

- **m_mul**: Returns a new matrix as the result of multiplication.
- **m_mult**: Multiplication with the result written to a provided output matrix.

### Power

- **m_pow**: Returns a new matrix raised to a power.
- **m_powp**: In-place matrix power.
- **m_powt**: Matrix power with the result written to a provided output matrix.

### Scalar Multiplication

- **m_kmul**: Returns a new matrix with scalar multiplication.
- **m_kmulp**: In-place scalar multiplication.
- **m_kmult**: Scalar multiplication with the result written to a provided output matrix.

### Scalar Division

- **m_kdiv**: Returns a new matrix with scalar division.
- **m_kdivp**: In-place scalar division.
- **m_kdivt**: Scalar division with the result written to a provided output matrix.

### Scalar Product

- **m_dot**: Returns the scalar product of two matrices.

### Transposition

- **m_transp**: Returns a new matrix as the result of transposition.
- **m_transpt**: Transposition with the result written to a provided output matrix.

### Sum Along a Direction

- **m_sumfd**: Returns a new matrix as the result of summing along a specified direction.
- **m_sumfdt**: Sum along a direction with the result written to a provided output matrix.

### Multiplication Along a Direction

- **m_mulfd**: Returns a new matrix as the result of multiplication along a specified direction.
- **m_mulfdt**: Multiplication along a direction with the result written to a provided output matrix.

### Element-wise Function Application

- **m_apply**: Returns a new matrix as the result of applying a function element-wise.
- **m_applyp**: In-place element-wise function application.
- **m_applyt**: Element-wise function application with the result written to a provided output matrix.

## Memory Management

- **matrix_free**: Free the memory occupied by a matrix.

**Note:** Please choose the appropriate function based on your specific requirements. Enjoy coding with matrices in C!

## License

This Matrix Operations Library is released under the MIT License. See the [LICENSE](LICENSE) file for details.
