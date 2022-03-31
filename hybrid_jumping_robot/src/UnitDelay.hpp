#ifndef HYBRID_JUMPING_ROBOT_UNITDELAY_HPP
#define HYBRID_JUMPING_ROBOT_UNITDELAY_HPP

#include "Types.hpp"

class UnitDelay {
private:
  Float64 last_input;

public:
  explicit UnitDelay(Float64 stating_input = 0);
  Float64 delay(Float64 input);
};


#endif //HYBRID_JUMPING_ROBOT_UNITDELAY_HPP
