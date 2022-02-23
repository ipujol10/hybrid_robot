#include "IMU_robot.hpp"

IMU::IMU() {
  ROS_INFO("IMU constructor");
}

void IMU::listener() {
  ros::Subscriber sub = nh.subscribe("/imu", 1, &IMU::callback, this);
}

void IMU::callback(const sensor_msgs::Imu &data) {
  quaternion = data.orientation;
  angular_velocity = data.angular_velocity;
  linear_acceleration = data.linear_acceleration;
}
