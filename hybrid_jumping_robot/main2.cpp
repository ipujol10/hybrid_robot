#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "prova");
  ros::NodeHandle n;
  ros::Rate rate(1);

  for (int i = 0; i < 10; i++) {
    ROS_INFO("Provant");
    rate.sleep();
  }
}