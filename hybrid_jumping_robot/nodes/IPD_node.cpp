#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "Inverted_pendulum_drive");
  ros::NodeHandle nh;
  IPD ipd("pid", M_PI_2, 100, 5e0, 1e-4, 9.9e-3);
  ipd.loop();
  return 0;
}