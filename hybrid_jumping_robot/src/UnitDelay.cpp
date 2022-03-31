#include "UnitDelay.hpp"
#include <stdexcept>

UnitDelay::UnitDelay(const std::vector<Float64> &stating_input) : last_input(stating_input) {} // NOLINT

std::vector<Float64> UnitDelay::delay(const std::vector<Float64> &input) {
  if (input.size() != last_input.size()) {
    throw std::invalid_argument("The number of states must be the same as before");
  }
  std::vector<Float64> output = last_input;
  last_input = input;
  return output;
}

UnitDelay::UnitDelay(Float64 starting_input) : last_input({starting_input}) {}

std::vector<Float64> UnitDelay::get_last_input() {
  return last_input;
}