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