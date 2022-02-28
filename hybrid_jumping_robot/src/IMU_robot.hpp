#include "Types.hpp"
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Imu.h>
#include <string>

#ifndef HYBRID_JUMPING_ROBOT_IMU_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_IMU_ROBOT_HPP


class IMU {
private:
  geometry_msgs::Quaternion quaternion;
//  std::array<Float64, 9> quaternion_covariance;
  geometry_msgs::Vector3 angular_velocity;
//  std::array<Float64, 9> angular_velocity_covariance;
  geometry_msgs::Vector3 linear_acceleration;
//  std::array<Float64, 9> linear_acceleration_covariance;
  int rate = 10;
  ros::NodeHandle nh;
  ros::Subscriber sub;

public:
  IMU();

  void listener();

  void callback(const sensor_msgs::Imu &data);

//  geometry_msgs::Quaternion get_quaternion();


};


#endif //HYBRID_JUMPING_ROBOT_IMU_ROBOT_HPP
