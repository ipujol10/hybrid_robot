#ifndef HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP
#define HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP

#include "Types.hpp"
#include <Eigen/Dense>


class StateFeedback {
private:
  Eigen::MatrixXd K; //!< Control matrix

public:
  StateFeedback();

  StateFeedback(const Eigen::MatrixXd &K);

  Eigen::MatrixXd get_action(const Eigen::MatrixXd &x);
};


#endif //HYBRID_JUMPING_ROBOT_STATEFEEDBACK_HPP
