#ifndef HYBRID_JUMPING_ROBOT_KINEMATICS_HPP
#define HYBRID_JUMPING_ROBOT_KINEMATICS_HPP

#include "Types.hpp"

#ifndef g
#define g 9.81
#endif //g

class KNM {
private:
  Float64 R; //!< radius of the wheel
  Float64 d; //!< distance from the wheel center to the center of mass of the body
  Float64 mb; //!< mass of the body
  Float64 mw; //!< mass of the wheels
  Float64 mT; //!< total mass of the robot
  Float64 Iw; //!< inertia of the wheel
  Float64 Ib; //!< inertia of the body

public:
  /// Initialize the kinematics
  /// \param R radius of the wheel
  /// \param d distance from the wheel center to the center of mass of the body
  /// \param mb mass of the body
  /// \param mw mass of the wheels
  /// \param Ib the inertia of the body
  KNM(Float64 R, Float64 d, Float64 mb, Float64 mw, Float64 Ib);

  KNM();

private:
  /// The function describing the second derivative of the body angle (theta) or the angular acceleration
  /// \param theta the state theta on the work
  /// \param phi2 the state phi2 on the work
  /// \return the value of the theta2
  [[nodiscard]] Float64 f1(Float64 theta, Float64 phi2) const;

  ///
  /// \param theta the state theta on the work
  /// \param theta1 the state theta1 on the work
  /// \param theta2 the state theta2 on the work
  /// \return the value of the phi2
  [[nodiscard]] Float64 f2(Float64 theta, Float64 theta1, Float64 theta2) const;

  /// obtain the Inertia of the wheels
  /// \return the inertia
  [[nodiscard]] Float64 calculate_Iw() const;

  /// Obtain the torque needed to make it stable
  /// \param theta the angle of the body
  /// \return torque-tau
  [[nodiscard]] Float64 tau(Float64 theta) const;

  /// Obtain the friction force to make it stable
  /// \param param the input value
  /// \param theta true: the parameter is theta. Else: the parameter is tau
  /// \return friction force
  [[nodiscard]] Float64 friction_force(Float64 param, bool theta = true) const;

public:
  /// the first value on the linearized model
  /// \param theta angle of the body
  /// \param phi2 angular acceleration of the wheels
  /// \return the value
  [[nodiscard]] Float64 a(Float64 theta, Float64 phi2) const;

  /// the control value on the linearized model
  /// \param theta angle of the body
  /// \return the value
  [[nodiscard]] Float64 b(Float64 theta) const;
};


#endif //HYBRID_JUMPING_ROBOT_KINEMATICS_HPP
