#include "Types.hpp"
#include "Data.hpp"
#include <geometry_msgs/Quaternion.h>
#include <cmath>

#ifndef HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP
#define HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP


namespace conv {
  Float64 get_correct_pitch(Float64 pitch, Float64 roll);

  RPY quaternion_to_rpy(geometry_msgs::Quaternion q);
}


#endif //HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP
