//
// Created by woombat on 2/23/22.
//
#include "Types.hpp"
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
#include <string>
#include "Conversions.hpp"
#include <math.h>
#ifndef HYBRID_JUMPING_ROBOT_PID_CONTROLLER_HPP
#define HYBRID_JUMPING_ROBOT_PID_CONTROLLER_HPP

#endif //HYBRID_JUMPING_ROBOT_PID_CONTROLLER_HPP
class PID{

public:
    PID( const std::string &name, Float64 target,Float64 KP,Float64 KI,Float64 KD,Float64 sample_time,ros::Time current_time);
    void setSampleTime(Float64 sample_t);
    void setKp(Float64 proportional_gain);
    void setKi(Float64 integral_gain);
    void setKd(Float64 derivative_gain);
    void setWindup(Float64 windup);
    void setTarget(Float64 target);
    void clear();
    Float64 update(Float64 feedback_value, ros::Time current_time, bool limit = false, Float64 upper = 0, Float64 lower = 0);
    [[nodiscard]] Float64 get_target() const;


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
    Float64 Pitch;
    Float64 Roll;

private:
  static Float64 range_limiter(Float64 input, Float64 upper, Float64 lower);
};





