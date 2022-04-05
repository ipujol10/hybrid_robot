#include "Types.hpp"
#include "Data.hpp"
#include <geometry_msgs/Quaternion.h>
#include <cmath>
#include <acado_toolkit.hpp>
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

  /// Convert a vector into a nx1 matrix
  /// \param vector the vector to convert
  /// \return the matrix
  ACADO::DMatrix vector_to_matrix(const std::vector<Float64> &vector);

  /// convert a nx1 matrix into a vector
  /// \param M the matrix
  /// \return the vector
  std::vector<Float64> matrix_to_vector(const ACADO::DMatrix &M);
}


#endif //HYBRID_JUMPING_ROBOT_CONVERSIONS_HPP
