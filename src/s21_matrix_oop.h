#ifndef CPP1_S21_MATRIX_PLUS_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIX_PLUS_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>

#define DEFINED_VALUE 1

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  double& operator()(int i, int j);
  void operator=(const S21Matrix& other);
  void operator=(S21Matrix&& other);
  S21Matrix operator*(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  S21Matrix operator*(const double num);
  void operator*=(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  void CreateMatrix();
  void DeleteMatrix();
  double FindDeterminant(const S21Matrix& other);
  S21Matrix AlgebricComplement();
  void Fill_matrix();

  int get_cols() const;
  void set_cols(const int col);
  int get_rows() const;
  void set_rows(const int row);

 private:
  int rows_, cols_;
  double** matrix_;
};

#endif  // CPP1_S21_MATRIX_PLUS_SRC_S21_MATRIX_OOP_H_