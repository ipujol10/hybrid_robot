#include "PID_tests.hpp"
#include <ros/ros.h>
#include <iostream>

PID_tests::PID_tests() : c(0.1), pid("pid", 0, 100, 1, 10, 0.01, ros::Time(0)) {}

bool PID_tests::test() {
  std::cout << c.output() << std::endl;
  for (int i = 0; i < 100; i++) {
    auto u = pid.update(c.output(), ros::Time((i + 1) * c.timeStep));
    c.update(u);
    std::cout << c.output() << std::endl;
  }
  return true;
}