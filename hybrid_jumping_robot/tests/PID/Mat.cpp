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

Mat Mat::operator*(const Mat &b) {
  std::vector<std::vector<Float64>> mat;
//  for ()
}

std::vector<Float64> Mat::operator[](int i) {
  return mat[i];
}
