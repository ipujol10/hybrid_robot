#include "Conversions.hpp"
#include <tf/tf.h>
#include <stdexcept>

Float64 conv::get_correct_pitch(Float64 pitch, Float64 roll) {
  if (roll > M_PI_2) return M_PI - pitch; // if roll has changed "side" --> return the complementary of the pitch
  return pitch;
}

RPY conv::quaternion_to_rpy(geometry_msgs::Quaternion q) {
  tf::Quaternion quaternion(q.x, q.y, q.z, q.w); // construct the quaternion
  tf::Matrix3x3 m(quaternion); // convert it into matrix
  Float64 roll, pitch, yaw;
  m.getRPY(roll, pitch, yaw); // convert it to Roll-Pitch-Yaw
  return {roll, pitch, yaw};
}

ACADO::DMatrix conv::vector_to_matrix(const std::vector<Float64> &vector) {
  ACADO::DMatrix out(vector.size(), 1); // initialize the matrix
  for (int i = 0; i < vector.size(); i++) {
    out(i, 0) = vector.at(i); // set each row to the vector value
  }
  return out;
}

std::vector<Float64> conv::matrix_to_vector(const ACADO::DMatrix &M) {
  if (M.getNumCols() != 1) { // if the matrix has more than 1 column
    throw std::invalid_argument("The matrix must have Nx1 dimensions"); // throw exception
  }
  std::vector<Float64> out;
  for (int i = 0; i < M.getNumRows(); i++) {
    out.emplace_back(M(i, 0)); // for each value in matrix, append it to the vector
  }
  return out;
}
