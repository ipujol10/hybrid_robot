#include "Types.hpp"
#include <string>
#include <ros/ros.h>

#ifndef HYBRID_JUMPING_ROBOT_ACTUATOR_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_ACTUATOR_ROBOT_HPP


class Actuator {
private:
  std::string extension_connection = "/hybrid_robotV0_2/extension_base_joint_position_controller/command";
  Float64 extension_position = 0;
  ros::Publisher extension_publisher;
  ros::Rate rate;

public:
  Actuator();

  void set_extension_position(Float64 pos);
};


#endif //HYBRID_JUMPING_ROBOT_ACTUATOR_ROBOT_HPP
