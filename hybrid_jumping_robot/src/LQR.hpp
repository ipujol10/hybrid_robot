#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Types.hpp"
#include "Observer.hpp"
#include <acado_toolkit.hpp>


class LQR {
private:
  ACADO::DMatrix A; //!< Linear system
  ACADO::DMatrix B; //!< Linear system
  Observer observer; //!< The observer to estimate the states
  ACADO::LinearStateFeedback lqr; //!< LQR controller

public:
  LQR();

  LQR(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K, const ACADO::DMatrix &KObs,
      const std::vector<Float64> &initial_state, Float64 Ts);
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
