#include "Vel_robot.hpp"
#include <cmath>
#include <iostream>

Vel::Vel() : rate(100), pid("wheels", 0, 0.1, 1e-9, 1e-7, 0.01, ros::Time::now()),
             now_velocity(0), can_clear(false) {
  pid.setWindup(2);
  ros::NodeHandle nh;
  left_front_wheel_publisher = nh.advertise<std_msgs::Float64>(left_front_wheel_connection, 10);
  right_front_wheel_publisher = nh.advertise<std_msgs::Float64>(right_front_wheel_connection, 10);
  current_velocity_publisher = nh.advertise<std_msgs::Float64>(current_velocity_connection, 1);
  vel_sub = nh.subscribe(commanded_velocity_connection, 1, &Vel::velocity_callback, this);
  state_sub = nh.subscribe(joint_state_connection, 1, &Vel::now_vel_callback, this);
  ROS_ERROR("Velocity OK");
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
  ROS_INFO_THROTTLE(0.5, "Sending velocity: % 0.6f", vel);
  std_msgs::Float64 msg;
  msg.data = vel;
  left_front_wheel_publisher.publish(msg);
  right_front_wheel_publisher.publish(msg);
  ros::spinOnce();
  rate.sleep();
}

void Vel::velocity_callback(const std_msgs::Float64 &data) {
//  update_target(data.data);
  set_front_wheels_velocity(data.data);
//  ros::spinOnce();
}

void Vel::now_vel_callback(const sensor_msgs::JointState &data) {
  now_velocity = (data.velocity[3] + data.velocity[4]) / 2;
//  ROS_INFO_THROTTLE(0.5, "Velocity = % 0.4f", now_velocity);
//  if (abs(now_velocity) < 0.005) {
//    if (can_clear) {
//      ROS_ERROR("PID cleared");
//      pid.clear();
//      can_clear = false;
//    }
//  } else {
//    can_clear = true;
//  }
//  Float64 out;
//  if (get_pid_target() != 0) {
//    out = cap_PID_output(pid.update(now_velocity, ros::Time::now()), 1e0, -1e0);
//  } else {
//    out = cap_PID_output(pid.update(now_velocity, ros::Time::now()), 3, -3);
//  }
//  set_front_wheels_velocity(out);
  std_msgs::Float64 msg;
  msg.data = now_velocity;
  current_velocity_publisher.publish(msg);
//  rate.sleep();
//  ros::spinOnce();
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

void Vel::loop() {
//  ros::spinOnce();
//  rate.sleep();
  while (ros::ok()) {
    ros::spinOnce();
    rate.sleep();
  }
}

Float64 Vel::get_pid_target() {
  return pid.get_target();
}
