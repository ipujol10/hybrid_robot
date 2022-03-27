#include "LQR.hpp"
//#include <exception>

LQR::LQR() = default;

LQR::LQR(Float64 d, Float64 rad, Float64 mw, Float64 mb, Float64 Ib, Float64 point,
         int qs, int rs) : xs(qs), us(rs), Q(qs, qs), R(rs, rs) {
  KNM kinematics(rad, d, mb, mw, Ib);
  A = get_A(point, kinematics);
  B = get_B(point, kinematics);
}

ACADO::DMatrix LQR::get_A(Float64 theta, const KNM &kinematics) const {
  ACADO::DMatrix mat(2, 2);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(1, 0) = kinematics.a(theta, 0);
  mat(1, 1) = 0;
  return mat;
}

ACADO::DMatrix LQR::get_B(Float64 theta, const KNM &kinematics) const {
  ACADO::DMatrix mat(2, 1);
  mat(0, 0) = 0;
  mat(1, 0) = kinematics.b(theta);
  return mat;
}

void LQR::set_Q(const std::vector<Float64> &costs) {
  if (costs.size() != xs) {
    throw std::invalid_argument("The costs values don't match the number of states");
  }

  for (int i = 0; i < xs; i++) {
    Q(i, i) = costs.at(i);
  }
}

void LQR::set_R(const std::vector<Float64> &costs) {
  if (costs.size() != us) {
    throw std::invalid_argument("The costs values don't match the number of inputs");
  }

  for (int i = 0; i < us; i++) {
    R(i, i) = costs.at(i);
  }
}

ACADO::DMatrix LQR::Riccati(const std::vector<Float64> &state_costs, const std::vector<Float64> &input_costs) {
  set_Q(state_costs);
  set_R(input_costs);

  ACADO::DifferentialState theta, theta1, phi, phi1;
  ACADO::Parameter s11, s12, s22;
  auto q1 = state_costs.at(0);
  auto q2 = state_costs.at(1);
  auto a11 = A(1, 1);
  auto a12 = A(1, 2);
  auto a21 = A(2, 1);
  auto a22 = A(2, 2);
  auto b = B(1, 1);
  auto r = input_costs.at(0);
}

LQR::LQR(const ACADO::DMatrix &A, const ACADO::DMatrix &B): A(A), B(B) {
  xs = B.getNumRows();
  us = B.getNumCols();
}