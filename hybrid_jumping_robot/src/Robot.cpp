#include "Robot.hpp"

Robot::Robot(const std::string &name): name(name) {}

void Robot::set_front_vel(Float64 vel) {
  velocity.set_front_wheels_velocity(vel);
}

void Robot::set_actuator_position(Float64 pos) {
  actuator.set_extension_position(pos);
}
