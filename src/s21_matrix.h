#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void initMatrix();
  void copyMatrix(const S21Matrix& other);
  void clearMatrix();

 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int new_rows);
  void SetCols(int new_cols);

  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  bool EqMatrix(const S21Matrix& other);

  void PrintMatrix() const;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j);
};

#endif