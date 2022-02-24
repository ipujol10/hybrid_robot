#include "Hybrid_jumping_Robot.hpp"

Hybrid_jumping_Robot::Hybrid_jumping_Robot(ros::NodeHandle *nh, const std::string &name,
                                           Float64 velocity, Float64 wheelradii): robot(name, nh),
                                           moving(false), now_velocity(0), velocity(velocity),
                                           wheelradii(wheelradii), print_timer(std::time(0)),
                                           start_time(std::time(0)) {
  ros::Subscriber sub = nh->subscribe("/imu", 1, &Hybrid_jumping_Robot::imu_callback, this);
  go();
}

void Hybrid_jumping_Robot::imu_callback(const sensor_msgs::Imu &data) {
  // TODO: get orientation from quaternion
}

void Hybrid_jumping_Robot::move_robot(Float64 vel) {
  Float64 set_velocity = vel;

  if (!moving) now_velocity = 0;

  while (set_velocity <= now_velocity) {
    now_velocity -= 5;
    robot.set_front_vel(now_velocity);
  }

  robot.set_actuator_position(0);
}

void Hybrid_jumping_Robot::brake_robot(Float64 vel) {
  robot.set_actuator_position(0);
  robot.set_front_vel(vel);
}

void Hybrid_jumping_Robot::increase_velocity() {
  velocity += 1;
  if (moving) move_robot(-velocity);
}

void Hybrid_jumping_Robot::decrease_velocity() {
  velocity -= 1;
  if (moving) move_robot(-velocity);
}

void Hybrid_jumping_Robot::go() {
  move_robot(velocity);
}


