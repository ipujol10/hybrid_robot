#include "Mat.hpp"
#include <stdexcept>

Mat::Mat(std::vector<std::vector<Float64>> mat) : mat(mat) {
  rows = mat.size();
  cols = mat.begin()->size();
  for (const auto &row: mat) {
    if (row.size() != cols) throw std::invalid_argument("Rows doesn't have the same length");
  }
}

Mat::Mat(const Mat &mat) = default;

Mat Mat::operator*(const Mat &b) const {
  if (cols != b.rows) throw std::invalid_argument("Rows of the first matrix must match the columns of the second");
  std::vector<std::vector<Float64>> result;
  for (int i = 0; i < rows; i++) {
    std::vector<Float64> vector;
    for (int j = 0; j < b.cols; j++) {
      Float64 sum = 0;
      for (int k = 0; k < cols; k++) {
        sum += mat[i][k] * b(k, j);
      }
      vector.emplace_back(sum);
    }
    result.emplace_back(vector);
  }

  return Mat(result);
}

std::vector<Float64> Mat::operator[](int i) {
  return mat[i];
}

Float64 Mat::operator()(int i, int j) const {
  return mat.at(i).at(j);
}

Mat Mat::operator+(const Mat &b) const {
  if (cols != b.cols || rows != b.rows) throw std::invalid_argument("The sizes of the matrix must match");
  std::vector<std::vector<Float64>> result;
  result.resize(rows);
  for (int i = 0; i < rows; i++) {
    std::vector<Float64> vector;
    vector.reserve(cols);
    for (int j = 0; j < cols; j++) {
      vector.emplace_back(mat[i][j] + b.mat[i][j]);
    }
    result.emplace_back(vector);
  }
  return Mat{result};
}

Mat Mat::operator*(const Float64 &scalar) const {
  std::vector<std::vector<Float64>> result;
  result.reserve(rows);
  for (const auto &row: mat) {
    std::vector<Float64> vector;
    vector.reserve(cols);
    for (const auto &value: row) {
      vector.emplace_back(scalar * value);
    }
    result.emplace_back(vector);
  }
  return Mat{result};
}

Mat& Mat::operator=(const Mat& a) = default;

Mat Mat::operator+=(const Mat &b) const {
  return *this+b;
}

Mat& Mat::operator+=(const Mat &b) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      this->mat.at(i).at(j) += b.mat.at(i).at(j);
    }
  }
  return *this;
}
