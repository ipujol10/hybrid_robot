#include "Model.hpp"

Model::Model(int states, int inputs, int outputs) : X(states), U(inputs), Y(outputs) {
  A = Matrix(X, X);
  B = Matrix(X, U);
  C = Matrix(Y, X); /*NOLINT*/
  D = Matrix(Y, U);
}

Model::Model() = default;

void Model::set_model(const Matrix &a, const Matrix &b, const Matrix &c,
                      const Matrix &d) {
  if (!(a.rows() == a.cols() && a.rows() == 1 && a(0, 0) == 0)) {
    if (a.rows() != X || a.cols() != X) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->A = a;
  }
  if (!(b.rows() == b.cols() && b.rows() == 1 && b(0, 0) == 0)) {
    if (b.rows() != X || b.cols() != U) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->B = b;
  }
  if (!(c.rows() == c.cols() && c.rows() == 1 && c(0, 0) == 0)) {
    if (c.rows() != Y || c.cols() != X) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->C = c;
  }
  if (!(d.rows() == d.cols() && d.rows() == 1 && d(0, 0) == 0)) {
    if (d.rows() != Y || d.cols() != U) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->D = d;
  }
}

void Model::set_A(const Matrix &a) {
  if (!(a.rows() == a.cols() && a.rows() == 1 && a(0, 0) == 0)) {
    if (a.rows() != X || a.cols() != X) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->A = a;
  }
}

void Model::set_B(const Matrix &b) {
  if (!(b.rows() == b.cols() && b.rows() == 1 && b(0, 0) == 0)) {
    if (b.rows() != X || b.cols() != U) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->B = b;
  }
}

void Model::set_C(const Matrix &c) {
  if (!(c.rows() == c.cols() && c.rows() == 1 && c(0, 0) == 0)) {
    if (c.rows() != Y || c.cols() != X) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->C = c;
  }
}

void Model::set_D(const Matrix &d) {
  if (!(d.rows() == d.cols() && d.rows() == 1 && d(0, 0) == 0)) {
    if (d.rows() != Y || d.cols() != U) {
      throw std::invalid_argument("The dimensions of the matrix doesn't match with the model");
    }
    this->D = d;
  }
}

Matrix Model::get_A() const {
  return A;
}

Matrix Model::get_B() const {
  return B;
}

Matrix Model::get_C() const {
  return C;
}

Matrix Model::get_D() const {
  return D;
}