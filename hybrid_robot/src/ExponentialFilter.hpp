#ifndef HYBRID_JUMPING_ROBOT_EXPONENTIALFILTER_HPP
#define HYBRID_JUMPING_ROBOT_EXPONENTIALFILTER_HPP

#include "NoiseFilter.hpp"


class ExplFilter : public NoiseFilter {
private:
  Float64 st; //!< Last smoothed value
  Float64 alpha; //!< Smoothing factor
public:
  ExplFilter(Float64 alpha, Float64 initial_value = 0);
  Float64 smooth(Float64 new_reading) override;
  void reset(Float64 new_reading) override;
};


#endif //HYBRID_JUMPING_ROBOT_EXPONENTIALFILTER_HPP
