#ifndef HYBRID_JUMPING_ROBOT_KINEMATICS_HPP
#define HYBRID_JUMPING_ROBOT_KINEMATICS_HPP

#include "Types.hpp"

#ifndef g
#define g 9.81
#endif //g

//namespace knm {
//  /// The function describing the second derivative of the body angle (theta) or the angular acceleration
//  /// \param R radius of the wheel
//  /// \param d distance from the wheel center to the center of mass of the body
//  /// \param m_b mass body
//  /// \param Ib inertia of the body
//  /// \param theta the state theta on the work
//  /// \param phi2 the state phi2 on the work
//  /// \return the value of the theta2
//  Float64 f1(Float64 R, Float64 d, Float64 mb, Float64 Ib, Float64 theta, Float64 phi2);
//
//  /// The function describing the second derivative of the wheel angle (phi) or the angular acceleration
//  /// \param R radius of the wheel
//  /// \param d distance from the wheel center to the center of mass of the body
//  /// \param mb mass body
//  /// \param mw mass wheel
//  /// \param Iw inertia of the wheel
//  /// \param theta the state theta on the work
//  /// \param theta1 the state theta1 on the work
//  /// \param theta2 the state theta2 on the work
//  /// \return the value of the phi2
//  Float64 f2(Float64 R, Float64 d, Float64 mb, Float64 mw, Float64 Iw, Float64 theta, Float64 theta1, Float64 theta2);
//
//  Float64 calculate_Ib();
//
//  Float64 calculate_Iw();
//}

class knm {
private:
  Float64 R; //!< radius of the wheel
  Float64 d; //!< distance from the wheel center to the center of mass of the body
  Float64 mb; //!< mass of the body
  Float64 mw; //!< mass of the wheels
  Float64 Iw; //!< inertia of the wheel

public:
  /// Initialize the kinematics
  /// \param R radius of the wheel
  /// \param d distance from the wheel center to the center of mass of the body
  /// \param mb mass of the body
  /// \param mw mass of the wheels
  knm(Float64 R, Float64 d, Float64 mb, Float64 mw);

  /// The function describing the second derivative of the body angle (theta) or the angular acceleration
  /// \param theta the state theta on the work
  /// \param phi2 the state phi2 on the work
  /// \return the value of the theta2
  Float64 f1(Float64 theta, Float64 phi2);

  ///
  /// \param theta the state theta on the work
  /// \param theta1 the state theta1 on the work
  /// \param theta2 the state theta2 on the work
  /// \return the value of the phi2
  Float64 f2(Float64 theta, Float64 theta1, Float64 theta2);

  /// obtain the Inertia of the wheels
  /// \return the inertia
  Float64 calculate_Iw();
};


#endif //HYBRID_JUMPING_ROBOT_KINEMATICS_HPP
