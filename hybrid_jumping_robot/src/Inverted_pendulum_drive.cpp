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
