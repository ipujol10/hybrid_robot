#include "StateFeedback.hpp"

StateFeedback::StateFeedback() = default;

StateFeedback::StateFeedback(const Matrix &K) : K(K) { /*NOLINT*/

}

Matrix StateFeedback::get_action(const Matrix &x) {
  auto u = -K * x;
  return u;
}