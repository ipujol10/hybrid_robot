#include "Vel_robot.hpp"
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "Vel_node");
  ros::NodeHandle nh;
  Vel vel;
  vel.loop();
}