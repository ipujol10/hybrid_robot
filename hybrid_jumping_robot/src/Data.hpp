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
  N_2_states_phi_u
};
#endif //HYBRID_JUMPING_ROBOT_DATA_HPP
