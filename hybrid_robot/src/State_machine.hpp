//
// Created by woombat on 2/24/22.
//
#include "Types.hpp"
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <string>

#ifndef HYBRID_JUMPING_ROBOT_STATE_MACHINE_HPP
#define HYBRID_JUMPING_ROBOT_STATE_MACHINE_HPP


class State_machine {

public:
    State_machine();

private:
    void callback_pitch(const std_msgs::Float64 &data);
    void callback_vel(const std_msgs::Float64 &data);
    void callback_input(const std_msgs::String &data);
    void States(int state);

    ros::Subscriber imu_sub;
    ros::Subscriber vel_sub;
    ros::Subscriber state_machine_input;
    ros::Publisher state_machine_output;
    ros::Publisher state_pub;
    
    ros::Time balancing_time;
    ros::Duration duration;

    Float64 Pitch;
    Float64 Velocity;

    int state_sel;
    std::string input;
    bool state_change;
};


#endif //HYBRID_JUMPING_ROBOT_STATE_MACHINE_HPP
