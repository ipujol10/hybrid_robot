#include "Observer.hpp"

Observer::Observer(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K,
                   const std::vector<Float64> &initial_state) : A(A), B(B), C(C), K(K), delay(initial_state) {}

std::vector<Float64> Observer::observe(const std::vector<Float64> &u, const std::vector<Float64> &y) {
  auto u_m = conv::vector_to_matrix(u);
  auto y_m = conv::vector_to_matrix(y);
  auto x = conv::vector_to_matrix(delay.get_last_input());
  auto sum = B * u_m + A * x - K * (C * x - y_m);
  return delay.delay(conv::matrix_to_vector(sum));
}

Observer::Observer() = default;

void Observer::update_starting_conditions(const std::vector<Float64> &initial_state) {
  delay.update_starting_conditions(initial_state);
}