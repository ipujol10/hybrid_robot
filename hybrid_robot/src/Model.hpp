#ifndef HYBRID_JUMPING_ROBOT_MODEL_HPP
#define HYBRID_JUMPING_ROBOT_MODEL_HPP

#include "Types.hpp"

class Model {
public:
  const int X{}; //!< number of states
  const int U{}; //!< number of inputs
  const int Y{}; //!< number of outputs

private:
  Matrix A; //!< A matrix of the system
  Matrix B; //!< B matrix of the system
  Matrix C; //!< C matrix of the system
  Matrix D; //!< D matrix of the system

public:
  Model(int states, int inputs, int outputs);

  Model();

  Model(const Matrix &a, const Matrix &b, const Matrix &c, const Matrix &d);

  void
  set_model(const Matrix &a, const Matrix &b, const Matrix &c, const Matrix &d);

  void set_A(const Matrix &a);

  void set_B(const Matrix &b);

  void set_C(const Matrix &c);

  void set_D(const Matrix &d);

  [[nodiscard]] Matrix get_A() const;

  [[nodiscard]] Matrix get_B() const;

  [[nodiscard]] Matrix get_C() const;

  [[nodiscard]] Matrix get_D() const;
};


#endif //HYBRID_JUMPING_ROBOT_MODEL_HPP
