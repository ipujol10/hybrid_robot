#include "Kinematics.hpp"
#include <cmath>

Float64 knm::calculate_Iw() {
  return mw*pow(R, 2)/2;
}

knm::knm(Float64 R, Float64 d, Float64 mb, Float64 mw): R(R), d(d), mb(mb), mw(mw) {
  Iw = calculate_Iw();
}