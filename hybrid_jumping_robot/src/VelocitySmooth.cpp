#include "VelocitySmooth.hpp"

VelocitySmooth::VelocitySmooth(Float64 alpha, Float64 initial_reading) : filter(alpha), last_reading(initial_reading) {}

Float64 VelocitySmooth::smooth(Float64 new_reading, Float64 d_time) {
  auto new_velocity = (new_reading - last_reading) / d_time;
  return filter.smooth(new_velocity);
}

void VelocitySmooth::reset(Float64 new_reading) {
  last_reading = new_reading;
  filter.reset(0);
}