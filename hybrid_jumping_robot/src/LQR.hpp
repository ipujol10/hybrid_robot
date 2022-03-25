#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Kinematics.hpp"
#include <acado_toolkit.hpp>


class LQR {
private:
  ACADO::LinearStateFeedback lqr;
  ACADO::DMatrix A;
  ACADO::DMatrix B;
  KNM kinematics;

public:
  LQR();
  LQR(Float64 d, Float64 R, Float64 mw, Float64 mb, Float64 Ib, Float64 point);

private:
  [[nodiscard]] ACADO::DMatrix get_A(Float64 theta) const;

  [[nodiscard]] ACADO::DMatrix get_B(Float64 theta) const;
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
