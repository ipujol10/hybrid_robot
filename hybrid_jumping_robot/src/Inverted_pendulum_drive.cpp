#include "Inverted_pendulum_drive.hpp"
#include <iostream>
#include <fstream>

IPD::IPD(const std::string &name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd, Float64 sample_time, int state) :
    pid(name, target, Kp, Ki, Kd, sample_time, ros::Time::now()), rate(100), state(state), angular_velocity(.4) {
  ros::NodeHandle nh;
//    inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1000);
  inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1);
  inverted_pitch_sub = nh.subscribe(inverted_pitch_connection, 1, &IPD::callbackPitch, this);
  state_sub = nh.subscribe("/HJC/State_machine/State", 1, &IPD::callbackState, this);
  inverted_pos_sub = nh.subscribe(inverted_pos_connection, 1, &IPD::callbackPos, this);
  inverted_vel_sub = nh.subscribe(inverted_current_vel_connection, 1, &IPD::callbackVel, this);
  if (state == -1) {
    active = true;
  } else {
    active = false;
  }

  pid.setWindup(20.0);
  isPID = true;
}

IPD::IPD(const std::vector<Float64> &target, const ACADO::DMatrix &A, const ACADO::DMatrix &B, /*NOLINT*/
         const ACADO::DMatrix &C, const ACADO::DMatrix &K, const ACADO::DMatrix &KObs,
         const std::vector<Float64> &initial_state, int state) : lqr(A, B, C, K, KObs, initial_state), rate(100),
                                                                 state(state), sys_states(initial_state),
                                                                 target(target), angular_velocity(.4) {
  ros::NodeHandle nh;
  inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1);
  inverted_pitch_sub = nh.subscribe(inverted_pitch_connection, 1, &IPD::callbackPitch, this);
  state_sub = nh.subscribe("/HJC/State_machine/State", 1, &IPD::callbackState, this);
  if (state == -1) {
    active = true;
  } else {
    active = false;
  }
  isPID = false;
}


void IPD::callbackPitch(const std_msgs::Float64 &data) {
  Pitch = data.data;
}

void IPD::callbackVel(const std_msgs::Float64 &data) {
  Velocity = data.data;
}

void IPD::callbackPos(const std_msgs::Float64 &data) {
  Position = data.data;
}

void IPD::loop() {
  std::ofstream out;
  out.open("/home/ipujol/AAU/S10/catkin_ws/src/hybrid_robot/hybrid_jumping_robot/bagfiles/states.txt", std::ios::out);
  while (ros::ok()) {
    if (active) {
      std_msgs::Float64 data;
      Float64 velocity = 0;
      if (isPID) {
        velocity = pid.update(Pitch, ros::Time::now(), true, 30, -30);
      } else {
        std::vector<Float64> y{Pitch - target.at(0), Position - target.at(1), Velocity - target.back()};
        auto u = lqr.get_action(sys_states);
//        ROS_WARN("Action: %f", u.at(0));
        sys_states = lqr.get_states(u, y);
        velocity = sys_states.back();
//        ROS_WARN("Velocity: %f", velocity);
      }
      data.data = velocity;
      inverted_vel_pub.publish(data);
    } else if (!isPID) {
      std::vector<Float64> y{Pitch - target.at(0), Position - target.at(1), Velocity - target.back()};
      auto u = lqr.get_action(sys_states);
      out << "U: " << vector_to_string(u);
      sys_states = lqr.get_states(u, y);
    }
    out << "States: " << vector_to_string(sys_states);
    out << "\n";
    ros::spinOnce();
    rate.sleep();
  }
  out.close();
}

void IPD::callbackState(const std_msgs::Int8 &data) {
  if (data.data == state || state == -1) {
    active = true;
  } else {
    active = false;
  }
}

std::array<ACADO::DMatrix, 5> IPD::get_matrix() {
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
  ACADO::DMatrix C(4, 4);
  C(0, 0) = 1;
  C(1, 1) = 1;
  C(2, 2) = 1;
  C(3, 3) = 1;
  out.at(2) = C;

  // K matrix
  ACADO::DMatrix K(1, 4);
  K(0, 0) = 5.5667;
  K(0, 1) = -0.0156;
  K(0, 2) = 0.5959;
  K(0, 3) = -0.0352;
  out.at(3) = K;

  // K observer matrix
  ACADO::DMatrix KObs(4, 4);
  KObs(0, 0) = 1.0135;
  KObs(1, 0) = 0.0142;
  KObs(2, 0) = 2.7166;
  KObs(3, 0) = 2.8467;
  KObs(0, 1) = 0;
  KObs(1, 1) = 0.6181;
  KObs(2, 1) = 0;
  KObs(3, 1) = 0.0018;
  KObs(0, 2) = 0.0100;
  KObs(1, 2) = 0.0001;
  KObs(2, 2) = 1.0125;
  KObs(3, 2) = 0.0149;
  KObs(0, 3) = 0;
  KObs(1, 3) = 0.0109;
  KObs(2, 3) = 0.0007;
  KObs(3, 3) = 0.9087;
  out.at(4) = KObs;

  return out;
}

std::string IPD::vector_to_string(const std::vector<Float64> &vector) {
  std::string out = "[";
  for (auto el: vector) {
    out += std::to_string(el) + ", ";
  }
  out = out.substr(0, out.size() - 2) + "]\n";
  return out;
}