# Matrix Operations README

## Introduction

Welcome to the Matrix Operations library! This C++ library provides a set of operations for matrix manipulation, including basic arithmetic operations, transposition, calculation of complements, determinant, and inverse matrix. The library is designed to handle various exceptional situations, providing both functionality and safety.

## Matrix Class

### Constructors and Destructors

- **`S21Matrix()`**: A basic constructor that initializes a matrix of some predefined dimension.
- **`S21Matrix(int rows, int cols)`**: Parametrized constructor with the number of rows and columns.
- **`S21Matrix(const S21Matrix& other)`**: Copy constructor.
- **`S21Matrix(S21Matrix&& other)`**: Move constructor.
- **`~S21Matrix()`**: Destructor.

### Operations

- **`bool EqMatrix(const S21Matrix& other)`**: Checks matrices for equality with each other.
- **`void SumMatrix(const S21Matrix& other)`**: Adds the second matrix to the current one. Handles different matrix dimensions.
- **`void SubMatrix(const S21Matrix& other)`**: Subtracts another matrix from the current one. Handles different matrix dimensions.
- **`void MulNumber(const double num)`**: Multiplies the current matrix by a number.
- **`void MulMatrix(const S21Matrix& other)`**: Multiplies the current matrix by the second matrix. Handles cases where the number of columns of the first matrix is not equal to the number of rows of the second matrix.
- **`S21Matrix Transpose()`**: Creates a new transposed matrix from the current one and returns it.
- **`S21Matrix CalcComplements()`**: Calculates the algebraic addition matrix of the current one and returns it. Handles cases where the matrix is not square.
- **`double Determinant()`**: Calculates and returns the determinant of the current matrix. Handles cases where the matrix is not square.
- **`S21Matrix InverseMatrix()`**: Calculates and returns the inverse matrix. Handles cases where the matrix determinant is 0.

### Overloaded Operators

- **`+`**: Addition of two matrices. Handles different matrix dimensions.
- **`-`**: Subtraction of one matrix from another. Handles different matrix dimensions.
- **`*`**: Matrix multiplication and matrix multiplication by a number. Handles cases where the number of columns of the first matrix does not equal the number of rows of the second matrix.
- **`==`**: Checks for matrices equality (EqMatrix).
- **`=`**: Assignment of values from one matrix to another one.
- **`+=`**: Addition assignment (SumMatrix). Handles different matrix dimensions.
- **`-=`**: Difference assignment (SubMatrix). Handles different matrix dimensions.
- **`*=`**: Multiplication assignment (MulMatrix/MulNumber). Handles cases where the number of columns of the first matrix does not equal the number of rows of the second matrix.
- **`(int i, int j)`**: Indexation by matrix elements (row, column). Handles cases where the index is outside the matrix.

## Usage

Include the Matrix Operations library in your C++ project and use the provided class and operations to manipulate matrices efficiently and safely.

## Contributing

Contributions are welcome! Feel free to fork the repository, make your enhancements, and submit a pull request.
