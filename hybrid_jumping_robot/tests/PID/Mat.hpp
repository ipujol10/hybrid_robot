#include <vector>
#include "../../src/Types.hpp"

#ifndef TESTS_MAT_HPP
#define TESTS_MAT_HPP


class Mat {
private:
  std::vector<std::vector<Float64>> mat;
  int cols;
  int rows;

public:
  Mat(const Mat &mat);

  explicit Mat(std::vector<std::vector<Float64>> mat);

  Mat operator*(const Mat &b);

  Mat operator+(const Mat &b);

  Mat operator*(const Float64 &scalar);

  std::vector<Float64> operator[](int i);
};


#endif //TESTS_MAT_HPP
