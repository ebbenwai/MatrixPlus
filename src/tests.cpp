#include <gtest/gtest.h>

#include "s21_matrix.h"
TEST(Create, False) {
  ASSERT_THROW(S21Matrix matrix_b(0, -1), std::domain_error);
}

TEST(SetValue, False) {
  S21Matrix matrix_b(10, 10);
  ASSERT_THROW(matrix_b(11, 11) = 1, std::domain_error);
}

TEST(Constructors, CopyConstructor) {
  S21Matrix original(2, 3);
  original(1, 1) = 5.0;

  S21Matrix copy(original);

  EXPECT_EQ(copy.GetRows(), 2);
  EXPECT_EQ(copy.GetCols(), 3);
  EXPECT_EQ(copy(1, 1), 5.0);
}

TEST(Constructors, MoveConstructor) {
  S21Matrix original(2, 3);
  original(1, 1) = 5.0;
  S21Matrix moved(std::move(original));
  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 3);
  EXPECT_EQ(moved(1, 1), 5.0);
  EXPECT_EQ(original.GetRows(), 0);
  EXPECT_EQ(original.GetCols(), 0);
}

TEST(EqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(SumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 33.14;
  matrix_a(0, 1) = 3.556;
  matrix_a(1, 0) = -639.3;
  matrix_a(1, 1) = 10;

  matrix_b(0, 0) = -748.14;
  matrix_b(0, 1) = 1230.43;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -715;
  result(0, 1) = 1233.986;
  result(1, 0) = -639.6;
  result(1, 1) = 12;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(SumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.1524;
  matrix_a(0, 1) = 2340.556;

  matrix_b(0, 0) = -7528.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -20234.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::invalid_argument);
}

TEST(SubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  matrix_a.SubMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}

TEST(SubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::invalid_argument);
}

TEST(MulNumber, MultiplyByZero) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;

  matrix_a.MulNumber(0);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, MultiplyByNegativeNumber) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = 781.4;
  result(0, 1) = 0;
  result(1, 0) = 3;
  result(1, 1) = -20;

  matrix_a.MulNumber(-10);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, MultiplyByFractionalNumber) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 21.5;
  matrix_a(0, 1) = 2.54;
  matrix_a(1, 0) = 31.30;
  matrix_a(1, 1) = 43.30;

  result(0, 0) = 86;
  result(0, 1) = 10.16;
  result(1, 0) = 125.2;
  result(1, 1) = 173.2;

  matrix_a.MulNumber(4);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 42;
  matrix_a(0, 1) = 51;
  matrix_a(1, 0) = 63.6;
  matrix_a(1, 1) = 12;

  matrix_b(0, 0) = -37;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -1732.5;
  result(0, 1) = 102;
  result(1, 0) = -2395.2;
  result(1, 1) = 24;

  matrix_a.MulMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -1424;

  matrix_b(0, 0) = 642;
  matrix_b(0, 1) = 54;
  matrix_b(1, 0) = -35.5;
  matrix_b(1, 1) = 252;

  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::invalid_argument);
}

TEST(OperatorParentheses, True) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_EQ(matrix_a(0, 1), 2);
}

TEST(OperatorParentheses, False) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_NE(matrix_a(0, 1), 10);
}

TEST(OperatorPlus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 54;
  matrix_a(0, 1) = -1.556;
  matrix_a(1, 0) = -9.53;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -8.14;
  matrix_b(0, 1) = 10;
  matrix_b(1, 0) = -5.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 45.86;
  result(0, 1) = 8.444;
  result(1, 0) = -14.83;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a + matrix_b) == result);
}

TEST(OperatorMinus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 0;
  matrix_a(0, 1) = 22;
  matrix_a(1, 0) = -4;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = 0;
  matrix_b(0, 1) = 32;
  matrix_b(1, 0) = -13;
  matrix_b(1, 1) = 2;

  result(0, 0) = 0;
  result(0, 1) = -10;
  result(1, 0) = 9;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a - matrix_b) == result);
}

TEST(OperatorMultiplyMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -12.4;
  matrix_a(0, 1) = 4;
  matrix_a(1, 0) = 2;
  matrix_a(1, 1) = 5;

  matrix_b(0, 0) = 41;
  matrix_b(0, 1) = 43;
  matrix_b(1, 0) = 53;
  matrix_b(1, 1) = -0.54;

  result(0, 0) = -296.4;
  result(0, 1) = -535.36;
  result(1, 0) = 347;
  result(1, 1) = 83.3;

  ASSERT_TRUE((matrix_a * matrix_b) == result);
}

TEST(OperatorMultiplyNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 0.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -10.3;
  matrix_a(1, 1) = 23;

  result(0, 0) = 1.4;
  result(0, 1) = 0;
  result(1, 0) = -103;
  result(1, 1) = 230;

  ASSERT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);

  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a += matrix_b) == result);
}

TEST(OperatorSumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 313.1434;
  matrix_a(0, 1) = 130.53126;

  matrix_b(0, 0) = 13.14;
  matrix_b(0, 1) = 423;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 523;

  EXPECT_THROW((matrix_a += matrix_b), std::invalid_argument);
}

TEST(OperatorSubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 4;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -10;
  matrix_a(1, 1) = 123;

  matrix_b(0, 0) = 67;
  matrix_b(0, 1) = 10;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -63;
  result(0, 1) = -8;
  result(1, 0) = -7;
  result(1, 1) = 121;

  ASSERT_TRUE((matrix_a -= matrix_b) == result);
}

TEST(OperatorSubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 421;
  matrix_b(1, 0) = 3213;
  matrix_b(1, 1) = 0;

  EXPECT_THROW(matrix_a -= matrix_b, std::invalid_argument);
}

TEST(OperatorMulNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -123.123;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -2.3;
  matrix_a(1, 1) = 34;

  result(0, 0) = -246.246;
  result(0, 1) = 0;
  result(1, 0) = -4.6;
  result(1, 1) = 68;

  ASSERT_TRUE((matrix_a *= 2) == result);
}

TEST(OperatorMulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a *= matrix_b) == result);
}

TEST(OperatorMulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 32;
  matrix_b(1, 0) = -332.5;
  matrix_b(1, 1) = 25;

  EXPECT_THROW(matrix_a *= matrix_b, std::invalid_argument);
}

TEST(Transpose, True) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 13;
  matrix_a(0, 2) = 4;
  matrix_a(1, 0) = 12;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 1;
  matrix_a(2, 0) = 3;
  matrix_a(2, 1) = 45;
  matrix_a(2, 2) = 88;
  matrix_a(3, 0) = 8;
  matrix_a(3, 1) = 4;
  matrix_a(3, 2) = 2;

  result(0, 0) = 1;
  result(0, 1) = 12;
  result(0, 2) = 3;
  result(0, 3) = 8;
  result(1, 0) = 13;
  result(1, 1) = 5;
  result(1, 2) = 45;
  result(1, 3) = 4;
  result(2, 0) = 4;
  result(2, 1) = 1;
  result(2, 2) = 88;
  result(2, 3) = 2;
  S21Matrix res = matrix_a.Transpose();
  ASSERT_TRUE(res == result);
}

TEST(Determinant, Determinant1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;
  double det = matrix.Determinant();
  EXPECT_DOUBLE_EQ(det, 5);
}

TEST(Determinant, Determinant2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 112.4;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3.43;
  matrix(1, 1) = 4;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, 442.74);
}

TEST(Determinant, Determinant3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  double det = matrix.Determinant();

  EXPECT_NEAR(det, 0, 1e-9);
}

TEST(Determinant, Determinant4x4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 66.6;
  matrix(0, 1) = 2;
  matrix(0, 2) = 2.5;
  matrix(0, 3) = 2.5;

  matrix(1, 0) = 0;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(1, 3) = 21.315;

  matrix(2, 0) = 12.4;
  matrix(2, 1) = 8;
  matrix(2, 2) = 0.34;
  matrix(2, 3) = 21.5;

  matrix(3, 0) = 3.432;
  matrix(3, 1) = 9;
  matrix(3, 2) = 5;
  matrix(3, 3) = 23;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, 24325.0637544);
}

TEST(Determinant, InvalidMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

///////

// TEST(CalcComplements, SquareMatrix1x1) {
//     S21Matrix matrix(1, 1);
//     matrix(0, 0) = 5;

//     S21Matrix result = matrix.CalcComplements();

//     EXPECT_EQ(result.GetRows(), 1);
//     EXPECT_EQ(result.GetCols(), 1);
//     EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
// }

TEST(CalcComplements, SquareMatrix2x2) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);

  matrix1(0, 0) = 32;
  matrix1(0, 1) = -31;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = -2;
  matrix2(1, 0) = 31;
  matrix2(1, 1) = 32;

  EXPECT_TRUE(matrix2 == matrix1.CalcComplements());
}

TEST(CalcComplements, SquareMatrix3x3) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 4;
  matrix1(1, 2) = 2;
  matrix1(2, 0) = 5;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;

  matrix2(0, 0) = 0;
  matrix2(0, 1) = 10;
  matrix2(0, 2) = -20;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = -14;
  matrix2(1, 2) = 8;
  matrix2(2, 0) = -8;
  matrix2(2, 1) = -2;
  matrix2(2, 2) = 4;

  EXPECT_TRUE(matrix2.EqMatrix(matrix1.CalcComplements()));
}

TEST(CalcComplements, NonSquareMatrix) {
  S21Matrix matrix(1, 3);

  ASSERT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(Inverse, False) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::invalid_argument);
}

TEST(Inverse, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));
}

TEST(Get, True) {
  S21Matrix matrix_a(3, 3);

  matrix_a(0, 0) = 19;
  matrix_a(0, 1) = 3;
  matrix_a(0, 2) = 5;
  matrix_a(1, 0) = 2;
  matrix_a(1, 1) = 0;
  matrix_a(1, 2) = 0;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -5;
  matrix_a(2, 2) = 3;

  ASSERT_EQ(matrix_a.GetRows(), 3);
  ASSERT_EQ(matrix_a.GetCols(), 3);
}

TEST(Set, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 2;
  result(0, 1) = 5;

  result(1, 0) = 6;
  result(1, 1) = 3;

  result(2, 0) = 5;
  result(2, 1) = -2;
  matrix_a.SetCols(2);

  ASSERT_TRUE(matrix_a == result);
}

// TEST(InverseMatrix, SquareMatrix1x1) {
//   S21Matrix matrix(1, 1);
//   matrix(0, 0) = 2;
//   EXPECT_TRUE(matrix.InverseMatrix()(0, 0) == 0.5);
// }

TEST(InverseMatrix, SquareMatrix2x2) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);

  matrix1(0, 0) = 3;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 0;

  matrix2(0, 0) = 0;
  matrix2(0, 1) = 0.2;
  matrix2(1, 0) = 0.5;
  matrix2(1, 1) = -0.3;

  EXPECT_TRUE(matrix2.EqMatrix(matrix1.InverseMatrix()));
}

TEST(InverseMatrix, SquareMatrix3x3) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 4;
  matrix1(1, 2) = 2;
  matrix1(2, 0) = 1;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;

  matrix2(0, 0) = 0;
  matrix2(0, 1) = -0.5;
  matrix2(0, 2) = 1;
  matrix2(1, 0) = -0.25;
  matrix2(1, 1) = 0.25;
  matrix2(1, 2) = 0.25;
  matrix2(2, 0) = 0.5;
  matrix2(2, 1) = 0;
  matrix2(2, 2) = -0.5;

  EXPECT_TRUE(matrix2.EqMatrix(matrix1.InverseMatrix()));
}

TEST(InverseMatrix, ZeroMatrix) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 3;
  matrix(0, 1) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 3;

  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrix, NonSquareMatrix) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = 6;
  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}