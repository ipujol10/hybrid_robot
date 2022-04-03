#include "Conversions.hpp"
#include <tf/tf.h>

Float64 conv::get_correct_pitch(Float64 pitch, Float64 roll) {
  if (roll > M_PI_2) return M_PI - pitch;
  return pitch;
}

RPY conv::quaternion_to_rpy(geometry_msgs::Quaternion q) {
  tf::Quaternion quaternion(q.x, q.y, q.z, q.w);
  tf::Matrix3x3 m(quaternion);
  Float64 roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw);
  return {roll, pitch, yaw};
}

ACADO::DMatrix conv::vector_to_matrix(const std::vector<Float64> &vector) {
  ACADO::DMatrix out(vector.size(), 1);
  for (int i = 0; i < vector.size(); i++) {
    out(i, 1) = vector.at(i);
  }
  return out;
}

std::vector<Float64> conv::matrix_to_vector(const ACADO::DMatrix &M) {
  std::vector<Float64> out;
  for (int i = 0; i < M.getNumRows(); i++) {
    out.emplace_back(M(i, 1));
  }
  return out;
}
