#ifndef HYBRID_JUMPING_ROBOT_VELOCITYSMOOTH_HPP
#define HYBRID_JUMPING_ROBOT_VELOCITYSMOOTH_HPP

#include "ExponentialFilter.hpp"

class VelocitySmooth {
private:
  ExplFilter filter;
  Float64 last_reading;

public:
  VelocitySmooth(Float64 alpha, Float64 initial_reading = 0);

  Float64 smooth(Float64 new_reading, Float64 d_time);

  void reset(Float64 new_reading);
};


#endif //HYBRID_JUMPING_ROBOT_VELOCITYSMOOTH_HPP
