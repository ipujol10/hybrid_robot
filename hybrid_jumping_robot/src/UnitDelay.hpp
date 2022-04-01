#ifndef HYBRID_JUMPING_ROBOT_UNITDELAY_HPP
#define HYBRID_JUMPING_ROBOT_UNITDELAY_HPP

#include "Types.hpp"
#include <vector>

class UnitDelay {
private:
  std::vector<Float64> last_input;

public:
  explicit UnitDelay(const std::vector<Float64> &stating_input = {0});
  std::vector<Float64> delay(const std::vector<Float64> &input);
  std::vector<Float64> get_last_input();
};


#endif //HYBRID_JUMPING_ROBOT_UNITDELAY_HPP
