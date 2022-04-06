#include "Inverted_pendulum_drive.hpp"

IPD::IPD(const std::string &name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd, Float64 sample_time, int state) :
    pid(name, target, Kp, Ki, Kd, sample_time, ros::Time::now()), rate(100), state(state) {
  ros::NodeHandle nh;
//    inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1000);
  inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1);
  inverted_pitch_sub = nh.subscribe(inverted_pitch_connection, 1, &IPD::callbackPitch, this);
  state_sub = nh.subscribe("/HJC/State_machine/State", 1, &IPD::callbackState, this);
  if (state == -1) {
    active = true;
  } else {
    active = false;
  }

  pid.setWindup(20.0);
  isPID = true;
}

IPD::IPD(const std::vector<Float64> &target, const ACADO::DMatrix &A, const ACADO::DMatrix &B,
         const ACADO::DMatrix &C, const ACADO::DMatrix &K, const ACADO::DMatrix &KObs,
         const std::vector<Float64> &initial_state, int state) : lqr(A, B, C, K, KObs, initial_state), rate(100),
                                                                 state(state), sys_states(initial_state) {
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

void IPD::loop() {
  while (ros::ok()) {
    if (active) {
      std_msgs::Float64 data;
      Float64 velocity;
      if (isPID) {
        velocity = pid.update(Pitch, ros::Time::now(), true, 30, -30);
      } else {
        auto u = lqr.get_action(sys_states);
        sys_states = lqr.get_states(u, {Pitch});
        velocity = sys_states.back();
      }
      data.data = velocity;
      inverted_vel_pub.publish(data);
    }
    ros::spinOnce();
    rate.sleep();
  }
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
