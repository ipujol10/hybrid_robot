#include "Robot.hpp"
#include <ctime>

#ifndef HYBRID_JUMPING_ROBOT_HYBRID_JUMPING_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_HYBRID_JUMPING_ROBOT_HPP


class Hybrid_jumping_Robot {
private:
  bool moving;
  Float64 roll;
  Float64 pitch;
  Float64 now_velocity;
  Robot robot;
  Float64 velocity;
  Float64 wheelradii;
  geometry_msgs::Vector3 orientation;
  time_t print_timer;
  time_t start_time;

public:
  Hybrid_jumping_Robot(const std::string &name, Float64 velocity, Float64 wheelradii);

  void imu_callback(const sensor_msgs::Imu &data);

  void move_robot(Float64 vel);

  void brake_robot(Float64 vel);

  void increase_velocity();

  void decrease_velocity();

  void go();
};


#endif //HYBRID_JUMPING_ROBOT_HYBRID_JUMPING_ROBOT_HPP
