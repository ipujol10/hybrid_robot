#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Kinematics.hpp"
#include <acado_toolkit.hpp>


class LQR {
private:
  ACADO::LinearStateFeedback lqr;
  ACADO::DMatrix A;

public:
  LQR();
  LQR(Float64 d, Float64 R, Float64 mw, Float64 mb, Float64 Ib, Float64 Iw, const std::vector<Float64> &point);
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
