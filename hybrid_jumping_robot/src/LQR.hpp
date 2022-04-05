#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Types.hpp"
#include "Observer.hpp"


class LQR {
private:
//  ACADO::DMatrix A; //!< Linear system
//  ACADO::DMatrix B; //!< Linear system
  ACADO::DMatrix K; //!< Control matrix
  Observer observer; //!< The observer to estimate the states

public:
  LQR();

  LQR(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K, const ACADO::DMatrix &KObs,
      const std::vector<Float64> &initial_state);

  std::vector<Float64> get_action(const std::vector<Float64> &x);

  std::vector<Float64> get_states(const std::vector<Float64> &u, const std::vector<Float64> &y);
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
