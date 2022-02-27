#include "Vel_robot.hpp"
#include <cmath>
#include <iostream>

Vel::Vel() : rate(100), pid("wheels", 0, 0.1, 1e-9, 1e-7, 0.01, ros::Time::now()),
             now_velocity(0) {
  ros::NodeHandle nh;
  left_front_wheel_publisher = nh.advertise<std_msgs::Float64>(left_front_wheel_connection, 10);
  right_front_wheel_publisher = nh.advertise<std_msgs::Float64>(right_front_wheel_connection, 10);
  vel_sub = nh.subscribe(commanded_velocity_connection, 1, &Vel::velocity_callback, this);
  state_sub = nh.subscribe(joint_state_connection, 1, &Vel::now_vel_callback, this);
}

void Vel::set_left_front_wheel_velocity(Float64 vel) {
  std_msgs::Float64 msg;
  msg.data = vel;
  left_front_wheel_publisher.publish(msg);
  ros::spinOnce();
  rate.sleep();
}

void Vel::set_right_front_wheel_velocity(Float64 vel) {
  std_msgs::Float64 msg;
  msg.data = vel;
  right_front_wheel_publisher.publish(msg);
  ros::spinOnce();
  rate.sleep();
}

void Vel::set_front_wheels_velocity(Float64 vel) {
  std_msgs::Float64 msg;
  msg.data = vel;
  left_front_wheel_publisher.publish(msg);
  right_front_wheel_publisher.publish(msg);
  ros::spinOnce();
  rate.sleep();
}

void Vel::velocity_callback(const std_msgs::Float64 &data) {
  update_target(data.data);
  ros::spinOnce();
}

void Vel::now_vel_callback(const sensor_msgs::JointState &data) {
  now_velocity = (data.velocity[3] + data.velocity[4]) / 2;
//  ROS_INFO("Velocities:\n"
//           "\t 0: %f\n"
//           "\t 1: %f\n"
//           "\t 2: %f\n"
//           "\t 3: %f\n"
//           "\t 4: %f\n\n", data.velocity[0],data.velocity[1],data.velocity[2],data.velocity[3],data.velocity[4]);
//  ROS_INFO("Velocity wheels: %f",now_velocity);
  auto out = cap_PID_output(pid.update(now_velocity, ros::Time::now()));
  set_front_wheels_velocity(out);
//  set_front_wheels_velocity(pid.update(now_velocity, ros::Time::now()));
//  ROS_ERROR("aoihdsai");
  rate.sleep();
  ros::spinOnce();
}

void Vel::update_target(Float64 target) {
  pid.setTarget(target);
  set_front_wheels_velocity(pid.update(now_velocity, ros::Time::now()));
}

Float64 Vel::cap_PID_output(Float64 out, Float64 max, Float64 min) {
  if (out > max) return max;
  if (out < min) return min;
  return out;
}
