#include "Robot.hpp"

Robot::Robot(const std::string &name, ros::NodeHandle *nh): name(name), nh(nh), imu(nh), actuator(nh), velocity(nh) {}

void Robot::set_front_vel(Float64 vel) {
  velocity.set_front_wheels_velocity(vel);
}