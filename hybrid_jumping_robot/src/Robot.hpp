#include "IMU_robot.hpp"

#ifndef HYBRID_JUMPING_ROBOT_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_ROBOT_HPP


class Robot {
private:
  std::string name;
  IMU imu;
  // actuator
  // velocity
  ros::NodeHandle *nh;

public:
  Robot(const std::string &name, ros::NodeHandle *nh);
};


#endif //HYBRID_JUMPING_ROBOT_ROBOT_HPP
