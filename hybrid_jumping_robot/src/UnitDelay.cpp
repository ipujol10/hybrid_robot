#include "UnitDelay.hpp"

UnitDelay::UnitDelay(Float64 stating_input) : last_input(stating_input) {}

Float64 UnitDelay::delay(Float64 input) {
  Float64 output = last_input;
  last_input = input;
  return output;
}