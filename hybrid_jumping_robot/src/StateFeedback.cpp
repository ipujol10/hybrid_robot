#include "StateFeedback.hpp"
#include <iostream>

StateFeedback::StateFeedback() = default;

StateFeedback::StateFeedback(const Matrix &K) : K(K) { /*NOLINT*/

}

StateFeedback::StateFeedback(const Model &model, const Matrix &k, const Matrix &l, const Matrix &i) : model(model),
                                                                                                      X(model.X),
                                                                                                      Y(model.Y),
                                                                                                      U(model.U) {
  x_hat = Matrix(X, 1);
  u = Matrix(U, 1);
  r = Matrix(Y, 1);
  w_hat = Matrix(U, 1);
  L = Matrix(X, Y);
  I = Matrix(U, Y);
  K = Matrix(U, X);

  initialise(k, l, i);
}

StateFeedback::StateFeedback(const Matrix &A, const Matrix &B, const Matrix &C, const Matrix &D, const Matrix &k,
                             const Matrix &l, const Matrix &i) : model(A, B, C, D), X(A.cols()), U(B.cols()),
                                                                 Y(C.rows()) {
  x_hat = Matrix(X, 1);
  u = Matrix(U, 1);
  r = Matrix(Y, 1);
  w_hat = Matrix(U, 1);
  L = Matrix(X, Y);
  I = Matrix(U, Y);
  K = Matrix(U, X);

  initialise(k, l, i);
}

Matrix StateFeedback::get_action(const Matrix &x) {
  u = -K * x;
  return u;
}

void StateFeedback::initialise(const Matrix &k, const Matrix &l, const Matrix &i) {
  set_gains(k, l, i);

  // Nbar is to map the reference to the control offset. Here is precalculated
  Matrix sys(X + Y, X + U);
  sys << model.get_A(), model.get_B(), model.get_C(), model.get_D();

  // Find the inverse
  Matrix invSys(X + U, X + Y);

  if (U < Y) { // more outputs than inputs --> left inverse
    invSys = (sys.transpose() * sys).inverse() * sys.transpose();
  } else { // more inputs than outputs --> right inverse
    invSys = sys.transpose() * (sys * sys.transpose()).inverse();
  }

  // Split in Nx and Nu and calculate N
  N_bar = k * invSys.block(0, X, X, Y) + invSys.block(X, X, U, Y);
  ALC = model.get_A() - l * model.get_C();
}

Matrix StateFeedback::get_u() const {
  return u;
}

Matrix StateFeedback::estimate_state(const Matrix &y, Float64 dt) {
  // TODO: see if it has to change as it is probably a discretitatzion
  return x_hat + (ALC * x_hat + model.get_B() * u + L * y) * dt;
}

void StateFeedback::update(const Matrix &y, Float64 dt) {
  // Update the state estimate
  if (X == Y) { // if it's Full State Feedback
    x_hat = y; // directly the new x_hat are the measured states
  } else { // if it's not FSF
    x_hat = estimate_state(y, dt); // it needs to estimate the x_hat
  }

  // Calculate the control input to stabilize at 0
  u = -K * x_hat;

  // Calculate the offset control for reference tracking
  u += N_bar * r;

  // get the offset to control the disturbance w
  w_hat += I * (y - r) * dt;
  u += w_hat;
}

void StateFeedback::set_gains(const Matrix &k, const Matrix &l, const Matrix &i) {
  if (k.rows() != U || k.cols() != X) {
    throw std::invalid_argument("The dimension of K doesn't match the system");
  }
  K = k;

  if (!(l(0, 0) == 0 && l.rows() == l.cols() && l.rows() == 1)) {
    if (l.rows() != X || l.cols() != Y) {
      throw std::invalid_argument("The dimension of L doesn't match the system");
    }
    L = l;
  }

  if (!(i(0, 0) == 0 && i.rows() == i.cols() && i.rows() == 1)) {
    if (i.rows() != U || i.cols() != Y) {
      throw std::invalid_argument("The dimension of I doesn't match the system");
    }
    I = i;
  }
}