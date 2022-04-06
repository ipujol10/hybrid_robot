#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>
#include <cmath>

int main(int argc, char **argv) {
  ros::init(argc, argv, "Inverted_pendulum_drive");
  ros::NodeHandle nh;
  auto matrix = IPD::get_matrix();
  IPD ipd({M_PI_2, 0, 0, 0, 0}, matrix.at(0), matrix.at(1), matrix.at(2), matrix.at(3), matrix.at(4), {0, 0, 0, 0});
//  IPD ipd("pid", M_PI_2, 100, 5e0, 1e-4, 9.9e-3);
  ipd.loop();
  return 0;
}