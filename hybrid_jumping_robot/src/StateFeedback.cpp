#include "StateFeedback.hpp"

StateFeedback::StateFeedback() = default;

StateFeedback::StateFeedback(const Matrix &K) : K(K) { /*NOLINT*/

}

StateFeedback::StateFeedback(const Model &model) : model(model), X(model.X), Y(model.Y), U(model.U) {
  x_hat = Matrix(X, 1);
  u = Matrix(U, 1);
  r = Matrix(Y, 1);
  w_hat = Matrix(U, 1);
  L = Matrix(X, Y);
  I = Matrix(U, Y);
}

Matrix StateFeedback::get_action(const Matrix &x) {
  u = -K * x;
  return u;
}

void StateFeedback::initialise() {
  /*
   * Put here the N gain (Precompensator) // TODO
   * */

  ALC = model.get_A() - L * model.get_C();
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