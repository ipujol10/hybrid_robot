#include "LQR.hpp"

LQR::LQR() = default;

LQR::LQR(const Eigen::MatrixXd &K): K(K) { /*NOLINT*/

}

Eigen::MatrixXd LQR::get_action(const Eigen::MatrixXd &x) {
  auto u = -K * x;
  return u;
}