#ifndef HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP
#define HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP

#include "Types.hpp"
#include "Model.hpp"

class StateFeedback {
private:
  // Control gains
  Matrix K; //!< Control gain
  Matrix L; //!< estimator gain
  Matrix I; //!< integral control gain

  // Control variables
  Matrix x_hat; //!< state estimate
  Matrix u; //!< control input
  Matrix r; //!< reference input
  Matrix w_hat; //!< estimate disturbance model (integral)

  // System model
  const Model model;

  // Dimensions of the model
  const int X{}; //!< number of states
  const int U{}; //!< number of inputs
  const int Y{}; //!< number of outputs

public:
  StateFeedback();

  StateFeedback(const Matrix &K);

  StateFeedback(const Model &model);

  Matrix get_action(const Matrix &x);
};


#endif //HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP