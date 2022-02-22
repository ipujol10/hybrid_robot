#include "Actuator_robot.hpp"
#include <std_msgs/Float64.h>

Actuator::Actuator(ros::NodeHandle *nh): rate(10) {
  extension_publisher = nh->advertise<std_msgs::Float64>(extension_connection, 10);
}

void Actuator::set_extension_position(Float64 pos) {
  extension_publisher.publish(pos);
  rate.sleep();
}