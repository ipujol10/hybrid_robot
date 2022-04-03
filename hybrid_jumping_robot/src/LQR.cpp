#include "LQR.hpp"

LQR::LQR() = default;

LQR::LQR(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K,
         const ACADO::DMatrix &KObs, const std::vector<Float64> &initial_state) : K(K), observer(A, B, C, KObs,
                                                                                                 initial_state) {

}

std::vector<Float64> LQR::get_action(const std::vector<Float64> &x) {
  auto u = -K * conv::vector_to_matrix(x);
  return conv::matrix_to_vector(u);
}

std::vector<Float64> LQR::get_states(const std::vector<Float64> &u, const std::vector<Float64> &y) {
  return observer.observe(u, y);
}