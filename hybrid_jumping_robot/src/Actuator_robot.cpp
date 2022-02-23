#include "Actuator_robot.hpp"
#include <std_msgs/Float64.h>

Actuator::Actuator(): rate(10) {
  ROS_INFO("Actuator constructor");
  ros::NodeHandle nh;
  extension_publisher = nh.advertise<std_msgs::Float64>(extension_connection, 10);
}

void Actuator::set_extension_position(Float64 pos) {
  std_msgs::Float64 msg;
  msg.data = pos;
  extension_publisher.publish(msg);
  rate.sleep();
}