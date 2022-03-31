#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Types.hpp"
#include <acado_toolkit.hpp>


class LQR {
private:
  ACADO::DMatrix A; //!< Linear system
  ACADO::DMatrix B; //!< Linear system
  ACADO::DMatrix K; //!< The control Matrix

public:
  LQR();
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
