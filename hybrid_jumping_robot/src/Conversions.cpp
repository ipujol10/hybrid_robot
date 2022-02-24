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