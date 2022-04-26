#ifndef HYBRID_JUMPING_ROBOT_MODEL_HPP
#define HYBRID_JUMPING_ROBOT_MODEL_HPP

#include <Eigen/Dense>

class Model {
private:
  const int X; //!< number of states
  const int U; //!< number of inputs
  const int Y; //!< number of outputs

  Eigen::MatrixXd A; //!< A matrix of the system
  Eigen::MatrixXd B; //!< B matrix of the system
  Eigen::MatrixXd C; //!< C matrix of the system
  Eigen::MatrixXd D; //!< D matrix of the system

public:
  Model(int states, int inputs, int outputs);

  void
  set_model(const Eigen::MatrixXd &a, const Eigen::MatrixXd &b, const Eigen::MatrixXd &c, const Eigen::MatrixXd &d);

  void set_A(const Eigen::MatrixXd &a);

  void set_B(const Eigen::MatrixXd &b);

  void set_C(const Eigen::MatrixXd &c);

  void set_D(const Eigen::MatrixXd &d);
};


#endif //HYBRID_JUMPING_ROBOT_MODEL_HPP
