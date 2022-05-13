#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>

IPD initiate();

int main(int argc, char **argv) {
  ros::init(argc, argv, "State_feedback_node");
  ros::NodeHandle nh;
  auto ipd = initiate();
  return 0;
}

IPD initiate() {
  auto matrix = IPD::get_matrix();
  Matrix target{{M_PI_2},
                {0}};
  Matrix initial_state{{1.5},
                       {0}};
  IPD out(target, matrix.at(0), matrix.at(1), matrix.at(2), Matrix{{0}}, matrix.at(3), initial_state, 200, -1,
          matrix.at(4));
  return out;
}