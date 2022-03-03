//
// Created by woombat on 2/24/22.
//
#include "PID_controller.hpp"
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <string>

#include "Types.hpp"
#ifndef HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
#define HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP


class IPD {
private:
  PID pid;
  ros::Publisher inverted_vel_pub;
  ros::Subscriber inverted_pitch_sub;
  std::string inverted_vel_connection = "/HJC/Vel_robot/Set_velocity";
  std::string inverted_pitch_connection = "/HJC/IMU/Pitch";
  ros::Rate rate;

public:
    IPD(const std::string& name ,Float64 target, Float64 Kp, Float64 Ki, Float64 Kd ,Float64 sampletime);
    void loop();

private:
    void callbackPitch(const std_msgs::Float64 &data);
    Float64 Pitch;
};


#endif //HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
