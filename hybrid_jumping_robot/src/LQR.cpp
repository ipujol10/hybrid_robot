#include "LQR.hpp"

LQR::LQR() = default;

LQR::LQR(Float64 d, Float64 R, Float64 mw, Float64 mb, Float64 Ib, Float64 point) : kinematics(R, d, mb, mw, Ib) {
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