#include "IMU_robot.hpp"

IMU::IMU() {}

void IMU::listener() {
  sub = nh.subscribe("/imu", 1, &IMU::callback, this);
}

void IMU::callback(const sensor_msgs::Imu &data) {
  quaternion = data.orientation;
  angular_velocity = data.angular_velocity;
  linear_acceleration = data.linear_acceleration;
}
