#include "Simple_control.hpp"
#include "Mat.hpp"
#include "../../src/PID_controller.hpp"
#include <ros/ros.h>
#include <iostream>

int main() {
  auto c = Simple_control(0.1);
  std::cout << c.output() << std::endl;
  auto pid = PID("pid", 0, 100, 1, 10, c.timeStep, ros::Time(0));
  for (int i = 0; i < 100; i++) {
    auto u = pid.update(c.output(), ros::Time((i + 1) * c.timeStep));
    c.update(u);
    std::cout << c.output() << std::endl;
  }
  return 0;
}