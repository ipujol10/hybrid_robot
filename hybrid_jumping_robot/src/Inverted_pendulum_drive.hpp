//
// Created by woombat on 2/24/22.
//
#ifndef HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
#define HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP

#include "PID_controller.hpp"
#include "Types.hpp"
#include "LQR.hpp"
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <string>


class IPD {
private:
  PID pid;
  LQR lqr;
  ros::Publisher inverted_vel_pub;
  ros::Subscriber inverted_pitch_sub;
  ros::Subscriber state_sub;
  std::string inverted_vel_connection = "/HJC/Vel_robot/Set_velocity";
  std::string inverted_pitch_connection = "/HJC/IMU/Pitch";
  ros::Rate rate;
  std::vector<Float64> sys_states;
  int state;
  bool active;
  bool isPID;

public:
  IPD(const std::string &name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd, Float64 sample_time, int state = -1);

  IPD(const std::vector<Float64> &target, const ACADO::DMatrix &A, const ACADO::DMatrix &B,
      const ACADO::DMatrix &C, const ACADO::DMatrix &K, const ACADO::DMatrix &KObs,
      const std::vector<Float64> &initial_state, int state = -1);

  void loop();

  static std::array<ACADO::DMatrix, 5> get_matrix();

private:
  void callbackPitch(const std_msgs::Float64 &data);

  void callbackState(const std_msgs::Int8 &data);

  Float64 Pitch;
};


#endif //HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
