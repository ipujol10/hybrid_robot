#include "../../src/PID_controller.hpp"

#ifndef TESTS_PID_TEST_HPP
#define TESTS_PID_TEST_HPP

class PID_Test {
private:
  PID pid;
public:
  PID_Test();

  bool test();
};

#endif //TESTS_PID_TEST_HPP
