//
// Created by woombat on 2/24/22.
//
#ifndef HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
#define HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP

#include "PID_controller.hpp"
#include "Types.hpp"
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <string>
//#include <acado_toolkit.hpp>


class IPD {
private:
  PID pid;
//  ACADO::LinearStateFeedback lqr;
  ros::Publisher inverted_vel_pub;
  ros::Subscriber inverted_pitch_sub;
  ros::Subscriber state_sub;
  std::string inverted_vel_connection = "/HJC/Vel_robot/Set_velocity";
  std::string inverted_pitch_connection = "/HJC/IMU/Pitch";
  ros::Rate rate;
  int state;
  bool active;
  Float64 old_velocity;

public:
    IPD(const std::string& name , Float64 target, Float64 Kp, Float64 Ki, Float64 Kd , Float64 sample_time, int state = -1);
    void loop();

private:
    void callbackPitch(const std_msgs::Float64 &data);
    void callbackState(const std_msgs::Int8 &data);
    Float64 Pitch;
    Float64 filter(Float64 new_vel, Float64 old_vel, Float64 alpha);
};


#endif //HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
