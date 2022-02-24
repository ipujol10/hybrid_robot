#include "Vel_robot.hpp"

Vel::Vel(ros::NodeHandle *nh) : rate(100) {
  left_front_wheel_publisher = nh->advertise<std_msgs::Float64>(left_front_wheel_connection, 10);
  right_front_wheel_publisher = nh->advertise<std_msgs::Float64>(right_front_wheel_connection, 10);
  ros::Subscriber sub = nh->subscribe("/internal/stabilize/controller/velocity", 1, &Vel::velocity_callback, this);
}

void Vel::set_left_front_wheel_velocity(Float64 vel) {
  std_msgs::Float64 msg;
  msg.data = vel;
  left_front_wheel_publisher.publish(msg);
  rate.sleep();
}

void Vel::set_right_front_wheel_velocity(Float64 vel) {
  std_msgs::Float64 msg;
  msg.data = vel;
  right_front_wheel_publisher.publish(msg);
  rate.sleep();
}

void Vel::set_front_wheels_velocity(Float64 vel) {
  std_msgs::Float64 msg;
  msg.data = vel;
  left_front_wheel_publisher.publish(msg);
  right_front_wheel_publisher.publish(msg);
  rate.sleep();
}

void Vel::velocity_callback(const std_msgs::Float64 &data) {
  set_front_wheels_velocity(data.data);
}
