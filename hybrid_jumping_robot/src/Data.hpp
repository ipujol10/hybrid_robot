#include "Types.hpp"
#ifndef HYBRID_JUMPING_ROBOT_DATA_HPP
#define HYBRID_JUMPING_ROBOT_DATA_HPP
struct RPY {
  Float64 roll;
  Float64 pitch;
  Float64 yaw;
};

enum class System {
  NONE,
  N_2_states_phi_u,
  pole_placement, // poles = {0, -1, -3, -6.87565805306348}
  k_manual,
  tuned_manual,
  LQR,
  pole_placement_discrete // poles = {0.932884813030418 +   0.00310411766981547i, 0.932884813030418 -   0.00310411766981547i, 0.999841011936642 +  0.000158914166594503i, 0.999841011936642 -  0.000158914166594503i}
};
#endif //HYBRID_JUMPING_ROBOT_DATA_HPP
