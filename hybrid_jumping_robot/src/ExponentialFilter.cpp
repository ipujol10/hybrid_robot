#include "ExponentialFilter.hpp"

ExplFilter::ExplFilter(Float64 alpha, Float64 initial_value) : alpha(alpha), st(initial_value) {}

void ExplFilter::reset(Float64 new_reading) {
  st = new_reading;
}

Float64 ExplFilter::smooth(Float64 new_reading) {
//  st = alpha * new_reading + (1 - alpha) * st;
  st += alpha * (new_reading - st);
  return st;
}