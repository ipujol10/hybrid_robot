#include "Simple_control.hpp"

Simple_control::Simple_control(Float64 angle, Float64 x) : A({{0, 1},
                                                              {2, -1}}),
                                                           B({{0},
                                                              {1}}),
                                                           x0({{angle},
                                                               {x}}), x(x0), timeStep(0.01) {}

void Simple_control::update(Float64 u) {
  auto x1 = A * x + B * u;
  x += x1 * timeStep;
}

Float64 Simple_control::output() {
  return x(0,0);
}