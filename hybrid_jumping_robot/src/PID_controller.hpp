//
// Created by woombat on 2/23/22.
//
#include "Types.hpp"
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Imu.h>
#include <string>
#ifndef HYBRID_JUMPING_ROBOT_PID_CONTROLLER_HPP
#define HYBRID_JUMPING_ROBOT_PID_CONTROLLER_HPP

#endif //HYBRID_JUMPING_ROBOT_PID_CONTROLLER_HPP
class PID{

public:
    PID( const std::string &name, Float64 KP,Float64 KI,Float64 KD,ros::Time current_time,Float64 sample_time);
    void clear();
    void update(Float64 feedback_value, ros::Time current_time);
    void setSampleTime(Float64 sample_t);
    void setKp(Float64 proportional_gain);
    void setKi(Float64 integral_gain);
    void setKd(Float64 derivative_gain);
    void setWindup(Float64 windup);
    void imu_callback(const sensor_msgs::Imu &data);

private:
    ros::Time CurrentTime;
    Float64 SampleTime;
    Float64 SetPoint;
    ros::Time LastTime;
    Float64 P;
    Float64 I;
    Float64 D;
    Float64 Target;
    Float64 LastError;
    Float64 PTerm;
    Float64 ITerm;
    Float64 DTerm;
    Float64 Output;
    Float64 windup_guard;


};





