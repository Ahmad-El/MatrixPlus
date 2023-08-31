#include "s21_matrix_oop.h"
void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::DeleteMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}

double S21Matrix::FindDeterminant(const S21Matrix& other) {
  if (other.cols_ == 1) {
    return matrix_[0][0];
  }
  if (other.cols_ == 2) {
    return other.matrix_[0][0] * other.matrix_[1][1] -
           other.matrix_[0][1] * other.matrix_[1][0];
  }
  double det = 0;

  S21Matrix temp(other.rows_ - 1, other.cols_ - 1);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < temp.rows_; j++) {
      int flag = 0;
      for (int k = 0; k < temp.rows_; k++) {
        if (i == k) flag = 1;
        int row = j + 1, col = k + flag;
        temp.matrix_[j][k] = other.matrix_[row][col];
      }
    }
    int sign = (i % 2 == 1) ? -1 : 1;
    double result = FindDeterminant(temp);
    det += sign * other.matrix_[0][i] * result;
  }
  return det;
}

S21Matrix S21Matrix::AlgebricComplement() {
  S21Matrix other(rows_, cols_);
  int size = cols_;
  S21Matrix temp(size - 1, size - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      int flag_row = 0;
      for (int u = 0; u < temp.cols_; u++) {
        int flag_col = 0;
        if (u == i) flag_row = 1;
        for (int v = 0; v < temp.cols_; v++) {
          if (v == j) flag_col = 1;
          temp.matrix_[u][v] = matrix_[u + flag_row][v + flag_col];
        }
      }
      other.matrix_[i][j] = FindDeterminant(temp) * pow(-1, i + j);
    }
  }
  return other;
}

// MY FUNCTION
void S21Matrix::Fill_matrix() {
  int cnt = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = cnt++;
    }
  }
}

// Getter & Setter Functions
int S21Matrix::get_cols() const { return cols_; }

int S21Matrix::get_rows() const { return rows_; }

void S21Matrix::set_cols(const int col) {
  if (col <= 0){
    throw std::invalid_argument(
        "The size of matrix should be greater then zero");
  }
  S21Matrix temp(std::move(*this));
  rows_ = temp.rows_;
  cols_ = col;
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_ && j < temp.cols_; j++) {
      matrix_[i][j] = temp.matrix_[i][j];
    }
  }
}

void S21Matrix::set_rows(const int row) {
  if (row <= 0){
    throw std::invalid_argument(
        "The size of matrix should be greater then zero");
  }
  S21Matrix temp(std::move(*this));
  rows_ = row;
  cols_ = temp.rows_;
  CreateMatrix();
  for (int i = 0; i < rows_ && i < temp.rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = temp.matrix_[i][j];
    }
  }
}

double S21Matrix::find_determinant_second_way(){
  double determinat = 1;
  for (int i = 1; i < rows_; i++){
    for (int j = 0; j < i; j++){
      if(matrix_[i][j] != 0){
        double cof = matrix_[i][j] / matrix_[j][j];
        for(int k = 0; k < cols_; k++){
          double result = matrix_[i][k] - cof * matrix_[j][k];
          if(abs(result) < 1e-07) matrix_[i][k] = 0;
          else {matrix_[i][k] = result;}
        }
      }
    }
  }
  for (int i = 0; i < rows_; i ++){
    determinat *= matrix_[i][i];
  }
  return determinat;
}

double S21Matrix::find_determinant_third_way(){
  S21Matrix temp(*this), origin(*this);
  double del = 1;
  for (int i = 0; i < rows_; i ++){
    for (int j = 0; j < rows_; j++){
      if(j == i) continue;
      for (int k = 0; k < rows_; k++){
          temp(j, k) = (origin(i,i) * origin(j,k)) - (origin(j,i) * origin(i,k));
          temp(j, k) /= del;
        }
      }
    del = temp(i, i);
    origin = temp;
    // std::cout << std::endl<< "matrix = " << std::endl;
    // temp.print_matrix();
  }
  (*this) = std::move(temp);
  return temp(0, 0);
}
