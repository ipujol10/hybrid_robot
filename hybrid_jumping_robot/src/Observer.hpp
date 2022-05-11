#ifndef HYBRID_JUMPING_ROBOT_OBSERVER_HPP
#define HYBRID_JUMPING_ROBOT_OBSERVER_HPP

#include "UnitDelay.hpp"
#include "Conversions.hpp"

class Observer {
private:
  UnitDelay delay;
  ACADO::DMatrix A; //!< Discrete A system
  ACADO::DMatrix B; //!< Discrete B system
  ACADO::DMatrix C; //!< Discrete C system
  ACADO::DMatrix K; //!< Discrete gain for the observer

public:
  Observer();
  Observer(const ACADO::DMatrix &A, const ACADO::DMatrix &B, const ACADO::DMatrix &C, const ACADO::DMatrix &K,
           const std::vector<Float64> &initial_state);
  std::vector<Float64> observe(const std::vector<Float64> &u, const std::vector<Float64> &y);
};


#endif //HYBRID_JUMPING_ROBOT_OBSERVER_HPP