#ifndef HYBRID_JUMPING_ROBOT_LQR_HPP
#define HYBRID_JUMPING_ROBOT_LQR_HPP

#include "Types.hpp"
#include <Eigen/Dense>


class LQR {
private:
  Eigen::MatrixXd K; //!< Control matrix

public:
  LQR();

  LQR(const Eigen::MatrixXd &K);

  Eigen::MatrixXd get_action(const Eigen::MatrixXd &x);
};


#endif //HYBRID_JUMPING_ROBOT_LQR_HPP
