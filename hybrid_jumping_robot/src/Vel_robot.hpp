#include "Types.hpp"
#include "PID_controller.hpp"
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>
#include <string>

#ifndef HYBRID_JUMPING_ROBOT_VEL_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_VEL_ROBOT_HPP


class Vel {
private:
  ros::Publisher left_front_wheel_publisher;
  ros::Publisher right_front_wheel_publisher;
  ros::Publisher current_velocity_publisher;
  ros::Subscriber vel_sub;
  ros::Subscriber state_sub;
//  std::string left_front_wheel_connection = "/hybrid_robotV0_2/front_left_wheel_joint_effort_controller/command";
//  std::string right_front_wheel_connection = "/hybrid_robotV0_2/front_right_wheel_joint_effort_controller/command";
  std::string left_front_wheel_connection = "/hybrid_robotV0_2/front_left_wheel_joint_velocity_controller/command";
  std::string right_front_wheel_connection = "/hybrid_robotV0_2/front_right_wheel_joint_velocity_controller/command";
  std::string joint_state_connection = "/hybrid_robotV0_2/joint_states";
  std::string commanded_velocity_connection = "/HJC/Vel_robot/Set_velocity";
  std::string current_velocity_connection = "/HJC/Vel_robot/Current_velocity";
  ros::Rate rate;
  PID pid;

  Float64 now_velocity;
  bool can_clear;

private:
  static Float64 cap_PID_output(Float64 out, Float64 max = 10, Float64 min = -10);

  void set_left_front_wheel_velocity(Float64 vel);

  void set_right_front_wheel_velocity(Float64 vel);

  void set_front_wheels_velocity(Float64 vel);

  void velocity_callback(const std_msgs::Float64 &data);

  void now_vel_callback(const sensor_msgs::JointState &data);

public:
  Vel();

  void loop();

  void update_target(Float64 target);

  Float64 get_pid_target();
};


#endif //HYBRID_JUMPING_ROBOT_VEL_ROBOT_HPP
