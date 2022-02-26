#include "PID_test.hpp"
#include "Mat.hpp"
#include <iostream>

int main() {
  Mat mat1({{1, 2},
            {3, 4}});

  Mat mat2({{1},
            {2}});

  Mat mat3({{1, 0},
            {0, 1}});

  auto result1 = mat1 * mat2;
  auto result2 = mat1 + mat3;
  auto result3 = mat3 * 3;

  return 0;
}