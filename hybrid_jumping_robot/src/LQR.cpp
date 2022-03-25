#include "LQR.hpp"
#include <exception>

LQR::LQR() = default;

LQR::LQR(Float64 d, Float64 rad, Float64 mw, Float64 mb, Float64 Ib, Float64 point,
         int qs, int rs) : kinematics(rad, d, mb, mw, Ib), qs(qs), rs(rs), Q(qs, qs), R(rs, rs) {
  A = get_A(point);
  B = get_B(point);
}

ACADO::DMatrix LQR::get_A(Float64 theta) const {
  ACADO::DMatrix mat(2, 2);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(1, 0) = kinematics.a(theta, 0);
  mat(1, 1) = 0;
  return mat;
}

ACADO::DMatrix LQR::get_B(Float64 theta) const {
  ACADO::DMatrix mat(2, 1);
  mat(0, 0) = 0;
  mat(1, 0) = kinematics.b(theta);
  return mat;
}

void LQR::set_Q(const std::vector<Float64> &costs) {
  if (costs.size() != qs) {
    throw std::invalid_argument("The costs values don't match the number of states");
  }

  for (int i = 0; i < qs; i++) {
    Q(i, i) = costs.at(i);
  }
}

void LQR::set_R(const std::vector<Float64> &costs) {
  if (costs.size() != rs) {
    throw std::invalid_argument("The costs values don't match the number of inputs");
  }

  for (int i = 0; i < rs; i++) {
    R(i, i) = costs.at(i);
  }
}