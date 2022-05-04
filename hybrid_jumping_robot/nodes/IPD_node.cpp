#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>
#include <cmath>

int main(int argc, char **argv) {
  ros::init(argc, argv, "Inverted_pendulum_drive");
  ros::NodeHandle nh;
  auto matrix = IPD::get_matrix();
  Matrix target{{M_PI_2},
                {0}};
  Matrix initial_state{{1.5},
                       {0}};
  IPD ipd(target, matrix.at(0), matrix.at(1), matrix.at(2), Matrix{{0}}, matrix.at(3), initial_state, 200, -1,
          matrix.at(4));
//  IPD ipd(target, matrix.at(3), initial_state, 200);
//  IPD ipd("pid", M_PI_2, 100, 5e0, 1e-4, 9.9e-3);
  ipd.loop();
  return 0;
}