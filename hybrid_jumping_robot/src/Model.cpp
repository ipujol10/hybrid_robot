#include "Model.hpp"

Model::Model(int states, int inputs, int outputs) : X(states), U(inputs), Y(outputs) {
  A = Eigen::MatrixXd(X, X);
  B = Eigen::MatrixXd(X, U);
  C = Eigen::MatrixXd(Y, X); /*NOLINT*/
  D = Eigen::MatrixXd(Y, U);
}

void Model::set_model(const Eigen::MatrixXd &a, const Eigen::MatrixXd &b, const Eigen::MatrixXd &c,
                      const Eigen::MatrixXd &d) {
  if (!(a.rows() == a.cols() && a.rows() == 1 && a(0, 0) == 0)) {
    this->A = a;
  }
  if (!(b.rows() == b.cols() && b.rows() == 1 && b(0, 0) == 0)) {
    this->B = b;
  }
  if (!(c.rows() == c.cols() && c.rows() == 1 && c(0, 0) == 0)) {
    this->C = c;
  }
  if (!(d.rows() == d.cols() && d.rows() == 1 && d(0, 0) == 0)) {
    this->D = d;
  }
}

void Model::set_A(const Eigen::MatrixXd &a) {
  if (!(a.rows() == a.cols() && a.rows() == 1 && a(0, 0) == 0)) {
    this->A = a;
  }
}

void Model::set_B(const Eigen::MatrixXd &b) {
  if (!(b.rows() == b.cols() && b.rows() == 1 && b(0, 0) == 0)) {
    this->B = b;
  }
}

void Model::set_C(const Eigen::MatrixXd &c) {
  if (!(c.rows() == c.cols() && c.rows() == 1 && c(0, 0) == 0)) {
    this->C = c;
  }
}

void Model::set_D(const Eigen::MatrixXd &d) {
  if (!(d.rows() == d.cols() && d.rows() == 1 && d(0, 0) == 0)) {
    this->D = d;
  }
}