#include "Simple_control.hpp"
#include "../../src/PID_controller.hpp"

#ifndef PID_TEST_PID_TESTS_HPP
#define PID_TEST_PID_TESTS_HPP


class PID_tests {
private:
  PID pid;
  Simple_control c;

public:
  PID_tests();

  bool test();
};


#endif //PID_TEST_PID_TESTS_HPP
