#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(DEFINED_VALUE), cols_(DEFINED_VALUE) {
  CreateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0){
    throw std::invalid_argument(
        "The size of matrix should be greater then zero");
  }
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) DeleteMatrix();
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.cols_) return false;
  double places = 0.0000001;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) < places) {
      } else
        return false;
    }
  }
  return true;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}
void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}
void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}
void S21Matrix::operator*=(const double num) { MulNumber(num); }
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}
void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, the number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  double temp = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      temp = 0;
      for (int u = 0; u < cols_; u++) {
        temp += matrix_[i][u] * other.matrix_[u][j];
      }
      result.matrix_[i][j] = temp;
    }
  }
  *this = result;
}

void S21Matrix::operator=(const S21Matrix& other) {
  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}
void S21Matrix::operator=(S21Matrix&& other) {
  *this = other;
  other.DeleteMatrix();
}
double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_) {
    throw std::out_of_range("index is outside the matrix");
  }
  return matrix_[i][j];
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square!");
  }
  if (cols_ == 1) {
    S21Matrix result(rows_, cols_);
    result.matrix_[0][0] = matrix_[0][0];
    return result;
  } else if (cols_ == 2) {
    S21Matrix result(rows_, cols_);
    result.matrix_[0][0] = matrix_[1][1];
    result.matrix_[0][1] = -matrix_[1][0];
    result.matrix_[1][0] = -matrix_[0][1];
    result.matrix_[1][1] = matrix_[0][0];
    return result;
  } else {
    return AlgebricComplement();
  }
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square!");
  }
  return FindDeterminant(*this);
}

S21Matrix S21Matrix::InverseMatrix() {
  if (Determinant() == 0) {
    throw std::out_of_range("matrix determinant is 0");
  }
  S21Matrix result(rows_, cols_);
  if (cols_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  }
  if (rows_ != 1) {
    double determinant = (*this).Determinant();
    S21Matrix temp = (*this).Transpose();
    result = temp.CalcComplements();
    for (int i = 0; i < result.rows_; ++i) {
      for (int j = 0; j < result.cols_; ++j) {
        result.matrix_[i][j] /= determinant;
      }
    }
  }
  return result;
}