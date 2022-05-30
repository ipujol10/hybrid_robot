#include "Types.hpp"
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64.h>
#include <string>
#include "Conversions.hpp"

#ifndef HYBRID_JUMPING_ROBOT_IMU_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_IMU_ROBOT_HPP


class IMU {
private:
  geometry_msgs::Quaternion quaternion;
  geometry_msgs::Vector3 angular_velocity;
  geometry_msgs::Vector3 linear_acceleration;
  ros::NodeHandle nh;
  ros::Subscriber sub;
  ros::Publisher pub_angle;
  ros::Rate loop_rate;

public:
  IMU();

  void callback(const sensor_msgs::Imu &data);

  void loop();


};


#endif //HYBRID_JUMPING_ROBOT_IMU_ROBOT_HPP
