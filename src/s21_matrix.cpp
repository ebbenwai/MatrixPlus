#include "s21_matrix.h"

#include <cmath>
#include <cstring>

/* -------------- CONSTRUCTORS AND DESTRUCTORS -------------- */

void S21Matrix::initMatrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::domain_error(
        "ERROR: Rows and columns must be greater than zero");
  }
  rows_ = rows;
  cols_ = cols;
  initMatrix();
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  initMatrix();
  copyMatrix(other);
}

void S21Matrix::clearMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.clearMatrix();
}

S21Matrix::~S21Matrix() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

/* -------------- CONSTRUCTORS AND DESTRUCTORS -------------- */

void S21Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) {
    throw std::invalid_argument("Number of rows must be greater than zero");
  }

  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }

  rows_ = new_rows;
  initMatrix();
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols <= 0) {
    throw std::invalid_argument("Number of columns must be greater than zero");
  }

  if (matrix_ == nullptr) {
    throw std::logic_error("Matrix is not initialized");
  }

  for (int i = 0; i < rows_; ++i) {
    double *new_row = new double[new_cols];
    for (int j = 0; j < std::min(cols_, new_cols); ++j) {
      new_row[j] = matrix_[i][j];
    }
    delete[] matrix_[i];
    matrix_[i] = new_row;
  }

  cols_ = new_cols;
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/* -------------- OPERATORS -------------- */

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::domain_error("ERROR: segmentation fault");
  }
  return matrix_[row][col];
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  return *this += other;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  return *this -= other;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  return *this *= other;
}

S21Matrix S21Matrix::operator*(const double num) { return *this *= num; }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  }

  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }

  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    std::memcpy(matrix_[i], other.matrix_[i], sizeof(double) * cols_);
  }

  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

/* -------------- OPERATORS -------------- */

/* -------------- FUNCTIONS -------------- */

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("ERROR: invalid");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("ERROR: invalid");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_ || rows_ != other.cols_) {
    throw std::invalid_argument("ERROR");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = result;
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

double S21Matrix::Determinant() {
  if (rows_ <= 0 || cols_ <= 0 || rows_ != cols_) {
    throw std::invalid_argument("ERROR");
  }
  double det = 1.0;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int k = 0; k < rows_; k++) {
      int max_row = k;
      for (int i = k + 1; i < cols_; i++) {
        if (fabs(matrix_[i][k]) > fabs(matrix_[max_row][k])) {
          max_row = i;
        }
      }
      if (max_row != k) {
        for (int j = 0; j < rows_; j++) {
          double temp = matrix_[k][j];
          matrix_[k][j] = matrix_[max_row][j];
          matrix_[max_row][j] = temp;
        }
        det *= -1;
      }
      det *= matrix_[k][k];

      for (int i = k + 1; i < rows_; i++) {
        double ratio = matrix_[i][k] / matrix_[k][k];
        for (int j = k; j < cols_; j++) {
          matrix_[i][j] -= ratio * matrix_[k][j];
        }
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ <= 0 || rows_ <= 0 || rows_ != cols_) {
    throw std::invalid_argument(
        "ERROR: Rows and columns must be greater than zero and matrix must be "
        "square.");
  }

  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      int mi = 0;
      for (int m = 0; m < rows_; m++) {
        if (m == i) {
          continue;
        }
        int mj = 0;
        for (int n = 0; n < cols_; n++) {
          if (n == j) {
            continue;
          }
          minor.matrix_[mi][mj] = matrix_[m][n];
          mj++;
        }
        mi++;
      }
      double minor_det = minor.Determinant();
      result(i, j) = minor_det * std::pow(-1, (i + j));
    }
  }
  return result;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) return false;
    }
  }
  return true;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix copy(rows_, cols_);
  copy.copyMatrix(*this);
  double determ = copy.Determinant();
  if (determ == 0) {
    throw std::invalid_argument(
        "ERROR: The determinant of this matrix is 0. The inverse matrix does "
        "not exist.");
  }
  S21Matrix result(rows_, rows_);
  S21Matrix temp = CalcComplements();
  S21Matrix transpose_matrix = temp.Transpose();
  result = transpose_matrix * (1.0 / determ);
  return result;
}

/* -------------- FUNCTIONS -------------- */