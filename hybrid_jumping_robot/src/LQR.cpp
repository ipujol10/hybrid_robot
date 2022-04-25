#include "LQR.hpp"

LQR::LQR() = default;

LQR::LQR(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K,
         const ACADO::DMatrix &KObs, const std::vector<Float64> &initial_state) : K(K), observer(A, B, C, KObs,
                                                                                                 initial_state) {

}

Eigen::MatrixXd LQR::get_action(const Eigen::MatrixXd &x) {
  auto u = -K * x;
  return u;
}