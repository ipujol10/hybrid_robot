#include "Kinematics.hpp"
#include <cmath>

Float64 knm::calculate_Iw() const {
  return mw * pow(R, 2) / 2;
}

knm::knm(Float64 R, Float64 d, Float64 mb, Float64 mw) : R(R), d(d), mb(mb), mw(mw) {
  Iw = calculate_Iw();
  mT = mb + mw;
}

Float64 knm::f2(Float64 theta, Float64 theta1, Float64 theta2) const {
  auto term1 = R * d * mb * sin(theta) * theta2;
  auto term2 = R * d * mb * cos(theta) * pow(theta1, 2);
  auto term3 = pow(R, 2) * mT + Iw;
  return (term1 - term2) / term3;
}

Float64 knm::tau(Float64 theta) const {
  return d * g * mb * cos(theta);
}

Float64 knm::friction_force(Float64 param, bool theta) const {
  if (theta) {
    return tau(param) / R;
  }
  return param / R;
}