#include "Actuator_robot.hpp"
#include "Vel_robot.hpp"

#ifndef HYBRID_JUMPING_ROBOT_ROBOT_HPP
#define HYBRID_JUMPING_ROBOT_ROBOT_HPP


class Robot {
private:
  std::string name;
  Actuator actuator;
  Vel velocity;

public:
  Robot(const std::string &name);

  void set_front_vel(Float64 vel);

  void set_actuator_position(Float64 pos);
};


#endif //HYBRID_JUMPING_ROBOT_ROBOT_HPP
