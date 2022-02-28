#include <vector>
#include "../../src/Types.hpp"

#ifndef TESTS_MAT_HPP
#define TESTS_MAT_HPP


class Mat {
private:
  std::vector<std::vector<Float64>> mat;
  size_t cols;
  size_t rows;

public:
  Mat(const Mat &mat);

  explicit Mat(std::vector<std::vector<Float64>> mat);

  Mat operator*(const Mat &b) const;

  Mat operator+(const Mat &b) const;

  Mat operator*(const Float64 &scalar) const;

  std::vector<Float64> operator[](int i);

  Float64 operator()(int i, int j) const;

  Mat& operator=(const Mat& a);

  Mat operator+=(const Mat& b) const;

  Mat& operator+=(const Mat& b);
};


#endif //TESTS_MAT_HPP
