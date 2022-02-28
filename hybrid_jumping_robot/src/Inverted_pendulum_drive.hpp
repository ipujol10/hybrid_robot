//
// Created by woombat on 2/24/22.
//
#include "PID_controller.hpp"
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include "Types.hpp"
#ifndef HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
#define HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP


class IPD {

public:
    IPD(int argc, char **argv, std::string name ,Float64 target, Float64 Kp, Float64 Ki, Float64 Kd ,Float64 sampletime);
private:
    void callbackPitch(const std_msgs::Float64 &data);
    Float64 Pitch;
};


#endif //HYBRID_JUMPING_ROBOT_INVERTED_PENDULUM__HPP
