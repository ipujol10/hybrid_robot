#include "Vel_robot.hpp"

Vel::Vel() : rate(100) {
  ros::NodeHandle nh;
  left_front_wheel_publisher = nh.advertise<std_msgs::Float64>(left_front_wheel_connection, 10);
  right_front_wheel_publisher = nh.advertise<std_msgs::Float64>(right_front_wheel_connection, 10);
  ros::Subscriber vel_sub = nh.subscribe(commanded_velocity_connection, 1, &Vel::velocity_callback, this);
  ros::Subscriber state_sub = nh.subscribe(joint_state_connection, 1, &Vel::now_vel_callback, this);
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

void Vel::now_vel_callback(const sensor_msgs::JointState &data) {
  now_velocity = (data.velocity[3] + data.velocity[4]) / 2;
}
