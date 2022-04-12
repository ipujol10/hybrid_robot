//
// Created by woombat on 2/24/22.
//
#ifndef HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
#define HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP

#include "PID_controller.hpp"
#include "Types.hpp"
#include "LQR.hpp"
#include "VelocitySmooth.hpp"
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <string>


class IPD {
private:
  PID pid;
  LQR lqr;
  VelocitySmooth angular_velocity;
  ros::Publisher inverted_vel_pub;
  ros::Subscriber inverted_pitch_sub;
  ros::Subscriber state_sub;
  ros::Subscriber inverted_pos_sub;
  ros::Subscriber inverted_vel_sub;
  std::string inverted_vel_connection = "/HJC/Vel_robot/Set_velocity";
  std::string inverted_pitch_connection = "/HJC/IMU/Pitch";
  std::string inverted_current_vel_connection = "/HJC/Vel_robot/Current_velocity";
  std::string inverted_pos_connection = "/HJC/Vel_robot/Current_position";
  ros::Rate rate;
  std::vector<Float64> sys_states;
  std::vector<Float64> target;
  int state;
  bool active;
  bool isPID;
  ros::Time last_time;

  Float64 Pitch;
  Float64 PitchVel;
  Float64 Velocity;
  Float64 Position;
  Float64 Ts; //!< Sample time

public:
  IPD(const std::string &name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd, Float64 sample_time,
      int state = -1, Float64 frequency = 200);

  IPD(const std::vector<Float64> &target, const ACADO::DMatrix &A, const ACADO::DMatrix &B,
      const ACADO::DMatrix &C, const ACADO::DMatrix &K, const ACADO::DMatrix &KObs,
      const std::vector<Float64> &initial_state, Float64 frequency, int state = -1);

  void loop();

  static std::array<ACADO::DMatrix, 5> get_matrix();

private:
  void callbackPitch(const std_msgs::Float64 &data);

  void callbackState(const std_msgs::Int8 &data);

  void callbackVel(const std_msgs::Float64 &data);

  void callbackPos(const std_msgs::Float64 &data);

  static std::string vector_to_string(const std::vector<Float64> &vector);

  static std::vector<Float64> vector_sum(const std::vector<Float64> &a, const std::vector<Float64> &b, bool sum = false);
};


#endif //HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
