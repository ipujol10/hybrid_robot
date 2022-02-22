//
// Created by ipujol on 2/22/22.
//

#include "IMU_robot.hpp"

IMU::IMU(ros::NodeHandle *nh): nh(nh) {}

void IMU::listener() {
  ros::Subscriber sub = nh->subscribe("/imu", 1, &IMU::callback, this);
}

void IMU::callback(const sensor_msgs::Imu &data) {
  quaternion = data.orientation;
  angular_velocity = data.angular_velocity;
  linear_acceleration = data.linear_acceleration;
}
