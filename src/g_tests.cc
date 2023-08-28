#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Test, create) {
  S21Matrix defaultMatrix;

  S21Matrix obj(3, 3);
  EXPECT_EQ(3, obj.get_cols());
  EXPECT_EQ(3, obj.get_rows());
  EXPECT_EQ(defaultMatrix.get_cols(), defaultMatrix.get_rows());
}

TEST(Test, create2) {
  EXPECT_THROW(S21Matrix obj(-1, 3), std::invalid_argument);
}
TEST(Test, create3) {
  S21Matrix A(3, 3);
  EXPECT_THROW(A.set_cols(0), std::invalid_argument);
  S21Matrix B;
  EXPECT_THROW(B.set_rows(-1), std::invalid_argument);
}
TEST(Test, sum) {
  S21Matrix A(3, 3);
  S21Matrix B(A);
  S21Matrix C = A + B;
  A *= 2;
  ASSERT_TRUE(A.EqMatrix(C));
}
TEST(Test, sum2) {
  S21Matrix A(3, 3);
  S21Matrix B(A);
  B.SumMatrix(A);
  A *= 2;
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(Test, sum3) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_THROW(A += B, std::out_of_range);
}

TEST(Test, sub) {
  S21Matrix A(3, 3);
  S21Matrix B(A);
  S21Matrix C = A - B;
  A -= B;
  ASSERT_TRUE(A == C);
}

TEST(Test, sub2) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 2);
  EXPECT_THROW(A -= B, std::out_of_range);
}

TEST(Test, mul_by_number) {
  S21Matrix A(3, 3);
  A.Fill_matrix();
  S21Matrix B = A * 2;
  A += A;
  ASSERT_TRUE(A == B);
}
TEST(Test, eq) {
  S21Matrix A(3, 3);
  A.Fill_matrix();
  S21Matrix B;
  B = A;
  ASSERT_TRUE(A == B);
  A(0, 0) = 0;
  EXPECT_THROW(A(5, 5), std::out_of_range);
  ASSERT_FALSE(A == B);
}

TEST(Test, mul_by_matrix) {
  S21Matrix A(1, 3);
  A.Fill_matrix();
  S21Matrix B(3, 1);
  B.Fill_matrix();
  S21Matrix C = A * B;
  EXPECT_EQ(C(0, 0), 14);
  EXPECT_THROW(A *= A, std::out_of_range);
}
TEST(Test, mul_by_matrix_1) {
  S21Matrix A(1, 3);
  A.Fill_matrix();

  S21Matrix B(3, 1);
  B.Fill_matrix();

  A *= B;
  EXPECT_EQ(A(0, 0), 14);
}

TEST(Test, transpose) {
  S21Matrix A(3, 3);
  A.Fill_matrix();
  S21Matrix B = A.Transpose();
  A(0, 0) = 1;
  A(0, 1) = 4;
  A(0, 2) = 7;

  A(1, 0) = 2;
  A(1, 1) = 5;
  A(1, 2) = 8;

  A(2, 0) = 3;
  A(2, 1) = 6;
  A(2, 2) = 9;
  ASSERT_TRUE(A == B);
}

TEST(Test, calc_complemets_1) {
  S21Matrix A(3, 3), B(3, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 0;
  B(1, 1) = 4;
  B(1, 2) = 2;
  B(2, 0) = 5;
  B(2, 1) = 2;
  B(2, 2) = 1;

  A(0, 0) = 0;
  A(0, 1) = 10;
  A(0, 2) = -20;
  A(1, 0) = 4;
  A(1, 1) = -14;
  A(1, 2) = 8;
  A(2, 0) = -8;
  A(2, 1) = -2;
  A(2, 2) = 4;
  B = B.CalcComplements();
  ASSERT_TRUE(A == B);
}

TEST(Test, calc_complemets_2) {
  S21Matrix A(2, 2), B(2, 2);

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 0;
  B(1, 1) = 4;

  A(0, 0) = 4;
  A(0, 1) = 0;
  A(1, 0) = -2;
  A(1, 1) = 1;

  B = B.CalcComplements();
  ASSERT_TRUE(A == B);
}
TEST(Test, calc_complemets_3) {
  S21Matrix A(1, 1), B(1, 1);
  B(0, 0) = 1;
  A(0, 0) = 1;
  B = B.CalcComplements();
  ASSERT_TRUE(A == B);
}

TEST(Test, calc_complemets_4) {
  S21Matrix B(2, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 2;
  B(1, 0) = 0;
  B(1, 1) = 4;
  B(1, 2) = 4;
  B.set_cols(2);
  B.set_cols(3);
  B.set_rows(3);
  B.set_rows(2);

  EXPECT_THROW(B.CalcComplements(), std::out_of_range);
}

TEST(Test, determinant) {
  S21Matrix A(4, 4);
  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 1;
  A(0, 3) = 5;

  A(1, 0) = 5;
  A(1, 1) = 8;
  A(1, 2) = 9;
  A(1, 3) = 9;

  A(2, 0) = 3;
  A(2, 1) = 2;
  A(2, 2) = 5;
  A(2, 3) = 1;

  A(3, 0) = 9;
  A(3, 1) = 2;
  A(3, 2) = 8;
  A(3, 3) = 7;
  double result = 0, real_result = 540.0;
  result = A.Determinant();
  EXPECT_TRUE(fabs(result - real_result) < 1e-7);
}
TEST(Test, detreminant_2) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.Determinant(), std::out_of_range);
}

TEST(Test, inverse) {
  S21Matrix A(2, 2), B(2, 2);
  A(0, 0) = 2;
  A(0, 1) = 1;
  A(1, 0) = 4;
  A(1, 1) = 3;

  A = A.InverseMatrix();
  B(0, 0) = 1.5;
  B(0, 1) = -0.5;
  B(1, 0) = -2;
  B(1, 1) = 1;

  EXPECT_TRUE(A == B);
}

TEST(Test, inverse_2) {
  S21Matrix A(3, 3), B(3, 3);
  A(0, 0) = 2;
  A(0, 1) = 1;
  A(0, 2) = 4;

  A(1, 0) = 4;
  A(1, 1) = 3;
  A(1, 2) = 9;

  A(2, 0) = 2;
  A(2, 1) = 12;
  A(2, 2) = 5;

  A = A.InverseMatrix();
  B(0, 0) = 4.65;
  B(0, 1) = -2.15;
  B(0, 2) = 0.15;

  B(1, 0) = 0.1;
  B(1, 1) = -0.1;
  B(1, 2) = 0.1;

  B(2, 0) = -2.1;
  B(2, 1) = 1.1;
  B(2, 2) = -0.1;
  EXPECT_TRUE(A == B);
}
TEST(Test, inverse_3) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.InverseMatrix(), std::out_of_range);
}
TEST(Test, inverse_4) {
  S21Matrix A(1, 1);
  A(0, 0) = 4;
  A = A.InverseMatrix();
  S21Matrix B(1, 1);
  B(0, 0) = 0.25;
  EXPECT_TRUE(A == B);
}

TEST(Test, inverse_5) {
  S21Matrix A(3, 3);
  A.Fill_matrix();
  EXPECT_THROW(A.InverseMatrix(), std::out_of_range);
}
TEST(Test, move_matrix) {
  S21Matrix A, B(3, 3), C(3, 3);
  B.Fill_matrix();
  C.Fill_matrix();
  A = std::move(C);
  EXPECT_TRUE(A == B);
}
TEST(Test, coverage_1) {
  S21Matrix A(3, 3);
  A.Fill_matrix();
  S21Matrix B(A);
  B -= A;
  A.SubMatrix(A);
  EXPECT_TRUE(B == A);
}
// TEST(Test, example) {}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}