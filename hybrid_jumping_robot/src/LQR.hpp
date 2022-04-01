#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Types.hpp"
#include "Observer.hpp"
#include <acado_toolkit.hpp>


class LQR {
private:
  ACADO::DMatrix A; //!< Linear system
  ACADO::DMatrix B; //!< Linear system
  ACADO::DMatrix K; //!< The control Gain
  ACADO::DMatrix KObs; //!< The observer Gain
  Observer observer; //!< The observer to estimate the states
  ACADO::LinearStateFeedback lqr; //!< LQR controller

public:
  LQR();
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
