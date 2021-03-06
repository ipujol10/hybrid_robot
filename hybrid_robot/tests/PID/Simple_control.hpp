#include "Mat.hpp"

#ifndef TESTS_PID_TEST_HPP
#define TESTS_PID_TEST_HPP

class Simple_control {
private:
  Mat A;
  Mat B;
  Mat x0;
  Mat x;

public:
  Float64 timeStep;

public:
  Simple_control(Float64 angle = 0, Float64 x = 0);

  void update(Float64 u);

  Float64 output();
};

#endif //TESTS_PID_TEST_HPP
