#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Kinematics.hpp"
#include <acado_toolkit.hpp>


class LQR {
private:
  ACADO::LinearStateFeedback lqr;
  ACADO::DMatrix A; //!< Linear system
  ACADO::DMatrix B; //!< Linear system
  ACADO::DMatrix Q; //!< Cost on the states
  ACADO::DMatrix R; //!< Cost on the inputs
  KNM kinematics; //!< kinematics of the system
  int qs;
  int rs;

public:
  LQR();
  LQR(Float64 d, Float64 rad, Float64 mw, Float64 mb, Float64 Ib, Float64 point, int qs = 2, int rs = 1);

  void set_Q(const std::vector<Float64> &costs);

  void set_R(const std::vector<Float64> &costs);

private:
  [[nodiscard]] ACADO::DMatrix get_A(Float64 theta) const;

  [[nodiscard]] ACADO::DMatrix get_B(Float64 theta) const;
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
