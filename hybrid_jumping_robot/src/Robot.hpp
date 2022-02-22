#include "IMU_robot.hpp"
#include "Actuator_robot.hpp"
#include "Vel_robot.hpp"

#ifndef HYBRID_JUMPING_ROBOT_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_ROBOT_HPP


class Robot {
private:
  std::string name;
  IMU imu;
  Actuator actuator;
  Vel velocity;
  ros::NodeHandle *nh;

public:
  Robot(const std::string &name, ros::NodeHandle *nh);

  void set_front_vel(Float64 vel);
};


#endif //HYBRID_JUMPING_ROBOT_ROBOT_HPP
