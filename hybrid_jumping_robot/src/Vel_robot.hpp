#include "Types.hpp"
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <string>

#ifndef HYBRID_JUMPING_ROBOT_VEL_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_VEL_ROBOT_HPP


class Vel {
private:
  ros::Publisher left_front_wheel_publisher;
  ros::Publisher right_front_wheel_publisher;
//  ros::Publisher left_back_wheel_publisher;
//  ros::Publisher right_back_wheel_publisher;
  std::string left_front_wheel_connection = "/hybrid_robotV0_2/front_left_wheel_joint_effort_controller/command";
  std::string right_front_wheel_connection = "/hybrid_robotV0_2/front_right_wheel_joint_effort_controller/command";
//  std::string left_back_wheel_connection = "/hybrid_robotV0_2/back_left_wheel_joint_velocity_controller/command";
//  std::string right_back_wheel_connection = "/hybrid_robotV0_2/back_right_wheel_joint_velocity_controller/command";
  ros::Rate rate;

public:
  Vel(ros::NodeHandle *nh);

  void set_left_front_wheel_velocity(Float64 vel);

  void set_right_front_wheel_velocity(Float64 vel);

  void set_front_wheels_velocity(Float64 vel);

  void velocity_callback(const std_msgs::Float64 &data);
};


#endif //HYBRID_JUMPING_ROBOT_VEL_ROBOT_HPP
