#ifndef HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP
#define HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP

#include "Types.hpp"

class StateFeedback {
private:
  Matrix K; //!< Control matrix

public:
  StateFeedback();

  StateFeedback(const Matrix &K);

  Matrix get_action(const Matrix &x);
};


#endif //HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP
