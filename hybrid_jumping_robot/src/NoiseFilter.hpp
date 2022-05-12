#ifndef HYBRID_JUMPING_ROBOT_NOISEFILTER_HPP
#define HYBRID_JUMPING_ROBOT_NOISEFILTER_HPP

#include "Types.hpp"

class NoiseFilter {
public:
  virtual Float64 smooth(Float64 new_reading) = 0;
  virtual void reset(Float64 new_reading) = 0;
};


#endif //HYBRID_JUMPING_ROBOT_NOISEFILTER_HPP
