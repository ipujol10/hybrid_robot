#include "LQR.hpp"

LQR::LQR() = default;

LQR::LQR(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K,
         const ACADO::DMatrix &KObs, const std::vector<Float64> &initial_state, Float64 Ts) : A(A), B(B),
                                                                                              observer(A, B, C, KObs,
                                                                                                       initial_state) {
  lqr = ACADO::LinearStateFeedback(K, Ts);
}