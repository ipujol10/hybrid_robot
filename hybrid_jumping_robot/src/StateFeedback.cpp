#include "StateFeedback.hpp"

StateFeedback::StateFeedback() = default;

StateFeedback::StateFeedback(const Eigen::MatrixXd &K): K(K) { /*NOLINT*/

}

Eigen::MatrixXd StateFeedback::get_action(const Eigen::MatrixXd &x) {
  auto u = -K * x;
  return u;
}