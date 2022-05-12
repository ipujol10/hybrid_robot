#include "Types.hpp"
#include "Data.hpp"
#include <geometry_msgs/Quaternion.h>
#include <cmath>
#include <vector>

#ifndef HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP
#define HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP


namespace conv {
  /// Obtain a continuous pitch from 0º to 180º
  /// \param pitch pitch obtained from the IMU
  /// \param roll roll obtained from the IMU
  /// \return corrected pitch
  Float64 get_correct_pitch(Float64 pitch, Float64 roll);

  /// Convert a quaternion to Euler angles in the configuration of Roll-Pitch-Yaw
  /// \param q quaternion
  /// \return Roll-Pitch-Yaw
  RPY quaternion_to_rpy(geometry_msgs::Quaternion q);

  /// Convert from rpm to rad/s
  /// \param rpm velocity in rpm
  /// \return velocity in rad/s
  Float64 rpm_to_rads(Float64 rpm);

  /// Convert form rad/s to rpm
  /// \param rads velocity in rad/s
  /// \return velocity in rpm
  Float64 rads_to_rpm(Float64 rads);
}


#endif //HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP
