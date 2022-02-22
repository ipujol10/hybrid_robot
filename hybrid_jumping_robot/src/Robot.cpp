//
// Created by ipujol on 2/22/22.
//

#include "Robot.hpp"

Robot::Robot(const std::string &name, ros::NodeHandle *nh): name(name), nh(nh), imu(nh) {}
