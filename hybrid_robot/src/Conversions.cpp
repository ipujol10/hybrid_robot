#include "Conversions.hpp"
#include <tf/tf.h>

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

Float64 conv::rpm_to_rads(Float64 rpm) {
  return rpm * M_PI / 30;
}

Float64 conv::rads_to_rpm(Float64 rads) {
  return rads * 30 / M_PI;
}
