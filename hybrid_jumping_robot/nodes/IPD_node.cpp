#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>
#include <iostream>

std::array<ACADO::DMatrix, 5> get_matrix();

int main(int argc, char **argv) {
  ros::init(argc, argv, "Inverted_pendulum_drive");
  ros::NodeHandle nh;
  auto matrix = get_matrix();
  IPD ipd("pid", M_PI_2, 100, 5e0, 1e-4, 9.9e-3);
  ipd.loop();
  return 0;
}

std::array<ACADO::DMatrix, 5> get_matrix() {
  std::array<ACADO::DMatrix, 5> out;
  // A matrix
  ACADO::DMatrix A(4, 4);
  A(0, 2) = 1;
  A(1, 3) = 1;
  A(2, 0) = 270.4470;
  A(3, 0) = 283.4000;
  out.at(0) = A;

  // B matrix
  ACADO::DMatrix B(4, 1);
  B(2, 0) = 193.4632;
  B(3, 0) = 296.2963;
  out.at(1) = B;

  // C matrix
  ACADO::DMatrix C(1, 4);
  C(0, 1) = 1;
  out.at(2) = C;

  // K matrix
  ACADO::DMatrix K(1, 4);
  K(0, 0) = 9.8785;
  K(0, 1) = -0.0319;
  K(0, 2) = 1.1661;
  K(0, 3) = -0.0718;
  out.at(3) = K;

  // K observer matrix
  ACADO::DMatrix KObs(4, 1);
  KObs(0, 0) = 64.5609;
  KObs(1, 0) = 2.0552;
  KObs(2, 0) = 268.4990;
  KObs(3, 0) = 272.0976;
  out.at(4) = KObs;

  return out;
}