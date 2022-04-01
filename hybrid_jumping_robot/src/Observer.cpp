#include "Observer.hpp"

Observer::Observer(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K,
                   const std::vector<Float64> &initial_state) : A(A), B(B), C(C), K(K), delay(initial_state) {}

std::vector<Float64> Observer::observe(const std::vector<Float64> &u, const std::vector<Float64> &y) {
  auto u_m = vector_to_matrix(u);
  auto y_m = vector_to_matrix(y);
  auto x = vector_to_matrix(delay.get_last_input());
  auto sum = B * u_m + A * x - K * (C * x - y_m);
  return delay.delay(matrix_to_vector(sum));
}

ACADO::DMatrix Observer::vector_to_matrix(const std::vector<Float64> &vect) {
  ACADO::DMatrix out(vect.size(), 1);
  for (int i = 0; i < vect.size(); i++) {
    out(i, 1) = vect.at(i);
  }
  return out;
}

std::vector<Float64> Observer::matrix_to_vector(const ACADO::DMatrix &M) {
  std::vector<Float64> out;
  for (int i = 0; i < M.getNumRows(); i++) {
    out.emplace_back(M(i, 1));
  }
  return out;
}

Observer::Observer() = default;