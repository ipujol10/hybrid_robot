#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>
#include <std_msgs/Int8.h>

int state;

void callback(const std_msgs::Int8 &data) {
  state = data.data;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "two_wheel_stabilizing_node");
  ros::NodeHandle nh;
  ros::Subscriber state_sub = nh.subscribe("/HJC/State_machine/State", 1, callback);
  ros::Rate loop_rate(280);
  IPD ipd("stabilizing", 1.46, 60, 0.0, 0.5, 9.9e-3, 3);
  ipd.loop();
}