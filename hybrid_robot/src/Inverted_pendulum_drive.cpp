//#define PAUSE_SIM_DEBUG

#include "Inverted_pendulum_drive.hpp"
#include <iostream>

#ifdef FILES_OUTPUT_DEBUG
#include <fstream>
#endif
#ifdef PAUSE_SIM_DEBUG
#include <std_srvs/Empty.h>
#endif

IPD::IPD(const std::string &name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd, Float64 sample_time,
         int state, Float64 frequency) : pid(name, target, Kp, Ki, Kd, sample_time, ros::Time::now()), rate(frequency),
                                         state(state), angular_velocity(.4) {
  ros::NodeHandle nh;
//    inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1000);
  inverted_vel_pub = nh.advertise<std_msgs::Float64>("/HJC/Vel_robot/Set_velocity", 1);
  inverted_pitch_sub = nh.subscribe("/HJC/IMU/Pitch", 1, &IPD::callbackPitch, this);
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

  last_time = ros::Time::now();
  Ts = 1 / frequency;
}

IPD::IPD(const Matrix &target, const Matrix &K, const Matrix &initial_state,
         Float64 frequency, int state) : stateFeedback(K), rate(frequency), state(state),
                                         sys_states(initial_state - target), target(target), angular_velocity(.4) {
  ros::NodeHandle nh;
  inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1);
  inverted_pitch_sub = nh.subscribe(inverted_pitch_connection, 1, &IPD::callbackPitch, this);
  state_sub = nh.subscribe("/HJC/State_machine/State", 1, &IPD::callbackState, this);
  inverted_vel_sub = nh.subscribe(inverted_current_vel_connection, 1, &IPD::callbackVel, this);
  if (state == -1) {
    active = true;
  } else {
    active = false;
  }
  isPID = false;

  last_time = ros::Time::now();
  Ts = 1 / frequency;

  Pitch = initial_state(0, 0);
  PitchVel = initial_state(1, 0);
}

IPD::IPD(const Matrix &target, const Matrix &A, const Matrix &B, const Matrix &C, const Matrix &D, const Matrix &K,
         const Matrix &initial_state, Float64 frequency, int state, const Matrix &L,
         const Matrix &I) : stateFeedback(A, B, C, D, K, L, I), rate(frequency), state(state),
                            sys_states(initial_state - target), target(target), angular_velocity(.4) {
  ros::NodeHandle nh;
  inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1);
  inverted_pitch_sub = nh.subscribe(inverted_pitch_connection, 1, &IPD::callbackPitch, this);
  state_sub = nh.subscribe("/HJC/State_machine/State", 1, &IPD::callbackState, this);
  inverted_vel_sub = nh.subscribe(inverted_current_vel_connection, 1, &IPD::callbackVel, this);
  if (state == -1) {
    active = true;
  } else {
    active = false;
  }
  isPID = false;

  last_time = ros::Time::now();
  Ts = 1 / frequency;

  Pitch = initial_state(0, 0);
  Position = initial_state(0, 0);
  PitchVel = initial_state(2, 0);
  Velocity = initial_state(3, 0);
}


void IPD::callbackPitch(const std_msgs::Float64 &data) {
  auto newPitch = data.data;
  if (!(isnan(newPitch) || isinf(newPitch))) {
    Pitch = newPitch;
  }
  ros::Duration d_time = ros::Time::now() - last_time;
  PitchVel = angular_velocity.smooth(Pitch, d_time.toSec());
}

void IPD::callbackVel(const std_msgs::Float64 &data) {
  Velocity = data.data;
}

void IPD::callbackPos(const std_msgs::Float64 &data) {
  Position = data.data;
}

void IPD::loop() {
#ifdef PAUSE_SIM_DEBUG
  ros::NodeHandle nh;
#endif
#ifdef FILES_OUTPUT_DEBUG
  std::ofstream out;
  out.open("/home/ipujol/AAU/S10/catkin_ws/src/hybrid_robot/hybrid_jumping_robot/bagfiles/states.txt", std::ios::out);
  std::ofstream times;
  times.open("/home/ipujol/AAU/S10/catkin_ws/src/hybrid_robot/hybrid_jumping_robot/bagfiles/times.txt");
#endif
#ifdef PAUSE_SIM_DEBUG
  ros::ServiceClient pauseGazebo = nh.serviceClient<std_srvs::Empty>("/gazebo/pause_physics");
  ros::ServiceClient unpauseGazebo = nh.serviceClient<std_srvs::Empty>("/gazebo/unpause_physics");
  std_srvs::Empty pauseSrv;
  std_srvs::Empty unpauseSrv;
#endif
  auto lastTime = ros::Time::now();

  while (ros::ok()) {
#ifdef PAUSE_SIM_DEBUG
    pauseGazebo.call(pauseSrv);
#endif
    Matrix current_real_state{{Pitch},
                              {Position},
                              {PitchVel},
                              {Velocity}};
    sys_states = current_real_state - target;
    if (true) {
      std_msgs::Float64 data;
      Float64 velocity = 0;
      if (isPID) {
        velocity = pid.update(Pitch, ros::Time::now(), true, 30, -30);
      } else {
//        std::vector<Float64> y{Pitch - target.at(0), Position - target.at(1), PitchVel - target.at(2),
//                               Velocity - target.back()};
//        auto y = vector_sum({Pitch, Position, PitchVel, Velocity}, target);
//        auto y = vector_sum({Pitch, PitchVel}, target);
//        auto u = stateFeedback.get_action(sys_states);
        auto u = stateFeedback.update(sys_states, (ros::Time::now()-lastTime).toSec());
//        ROS_WARN("Action: %f", u.at(0));
//        sys_states = stateFeedback.get_states(u, sys_states);
//        velocity = sys_states.back();
        auto acc_rpm = conv::rads_to_rpm(u(0, 0));
        velocity = Velocity + acc_rpm * Ts;
        auto real_states = sys_states + target;
        ROS_INFO("acc (u) = % .5f", acc_rpm);
        ROS_INFO("[Pitch, Pitch_Velocity]: [% .5f, %.5f]", real_states(0, 0), real_states(1, 0));
        ROS_INFO("Velocity: % .5f\n", Velocity);
#ifdef FILES_OUTPUT_DEBUG
        out << "u: " << acc_rpm << "\n";
        out << "New Velocity: " << velocity << ", Current Velocity: " << Velocity << "\n";
#endif
//        ROS_WARN("Velocity: %f", velocity);
      }

      data.data = velocity;
      inverted_vel_pub.publish(data);
    }
//    out << "Pitch Velocity: " << PitchVel << "\n";
#ifdef FILES_OUTPUT_DEBUG
    out << "[Pitch, Pitch_Velocity]: " << sys_states + target << "\n";
    out << "\n";
    times << (ros::Time::now() - now).toNSec() << "\n";
#endif
#ifdef PAUSE_SIM_DEBUG
    unpauseGazebo.call(unpauseSrv);
#endif
    lastTime = ros::Time::now();
    ros::spinOnce();
    rate.sleep();
  }
#ifdef FILES_OUTPUT_DEBUG
  out.close();
#endif
}

void IPD::callbackState(const std_msgs::Int8 &data) {
  if (data.data == state || state == -1) {
    active = true;
  } else {
    active = false;
  }
}

//std::array<ACADO::DMatrix, 5> IPD::get_matrix() {
//  std::array<ACADO::DMatrix, 5> out;
//  // A matrix
//  ACADO::DMatrix A(4, 4);
//  A(0, 2) = 1;
//  A(1, 3) = 1;
//  A(2, 0) = 270.4470;
//  A(3, 0) = 283.4000;
//  out.at(0) = A;
//
//  // B matrix
//  ACADO::DMatrix B(4, 1);
//  B(2, 0) = 193.4632;
//  B(3, 0) = 296.2963;
//  out.at(1) = B;
//
//  // C matrix
//  ACADO::DMatrix C(4, 4);
//  C(0, 0) = 1;
//  C(1, 1) = 1;
//  C(2, 2) = 1;
//  C(3, 3) = 1;
//  out.at(2) = C;
//
//  // K matrix
//  ACADO::DMatrix K(1, 4);
//  K(0, 0) = 5.5667;
//  K(0, 1) = -0.0156;
//  K(0, 2) = 0.5959;
//  K(0, 3) = -0.0352;
//  out.at(3) = K;
//
//  // K observer matrix
//  ACADO::DMatrix KObs(4, 4);
//  KObs(0, 0) = 1.0135;
//  KObs(1, 0) = 0.0142;
//  KObs(2, 0) = 2.7166;
//  KObs(3, 0) = 2.8467;
//  KObs(0, 1) = 0;
//  KObs(1, 1) = 0.6181;
//  KObs(2, 1) = 0;
//  KObs(3, 1) = 0.0018;
//  KObs(0, 2) = 0.0100;
//  KObs(1, 2) = 0.0001;
//  KObs(2, 2) = 1.0125;
//  KObs(3, 2) = 0.0149;
//  KObs(0, 3) = 0;
//  KObs(1, 3) = 0.0109;
//  KObs(2, 3) = 0.0007;
//  KObs(3, 3) = 0.9087;
//  out.at(4) = KObs;
//
//  return out;
//}

std::array<Matrix, 5> IPD::get_matrix(const System &value) {
  std::array<Matrix, 5> out;
  Matrix A, B, C, K, L;
  switch (value) {
    case System::NONE:
      throw std::invalid_argument("A system must be selected (Different than 'NONE')");

    case System::N_2_states_phi_u:
      // A matrix
      A = Matrix{{0,                1},
                 {85.4043194374686, 0}};
      out.at(0) = A;

      // B matrix
      B = Matrix{{0},
                 {0.65293822199899}};
      out.at(1) = B;

      // C matrix
      C = Matrix{{1, 0},
                 {0, 1}};
      out.at(2) = C;

      // K matrix
      K = Matrix{{370.789576601112, 44.33501015724}};
      out.at(3) = K;

      L = Matrix{{1.00104772344165,   0.427165035127185},
                 {0.0049967972077693, 1.00006886107095}};
      out.at(4) = L;
      break;

    case System::pole_placement:
      A = Matrix{{0,                 0, 1, 0},
                 {0,                 0, 0, 1},
                 {47.2746736626568,  0, 0, 0},
                 {-1.34433823959577, 0, 0, 0}};
      out.at(0) = A;

      // B matrix
      B = Matrix{{0},
                 {0},
                 {0.0968725463390153},
                 {-0.00331057279509083}};
      out.at(1) = B;

      // C matrix
      C = Matrix{{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
      out.at(2) = C;

      // K matrix
      K = Matrix{{802.882847764951, 0, 139.094311369446, 784.988650429386}};
      out.at(3) = K;

      L = Matrix{{0,                 0,  1,  0},
                 {0,                 10, 0,  1},
                 {47.2746736626568,  0,  30, 0},
                 {-1.34433823959577, 0,  0,  68.7565805306348}};
      out.at(4) = L;
      break;

    case System::k_manual:
      A = Matrix{{0,                 0, 1, 0},
                 {0,                 0, 0, 1},
                 {47.2746736626568,  0, 0, 0},
                 {-1.34433823959577, 0, 0, 0}};
      out.at(0) = A;

      // B matrix
      B = Matrix{{0},
                 {0},
                 {0.0968725463390153},
                 {-0.00331057279509083}};
      out.at(1) = B;

      // C matrix
      C = Matrix{{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
      out.at(2) = C;

      // K matrix
      K = Matrix{{802.88,0,139.09,784.99}};
      out.at(3) = K;

      L = Matrix{{10,                0,  1,  0},
                 {0,                 20, 0,  1},
                 {47.2746736626568,  0,  30, 0},
                 {-1.34433823959577, 0,  0,  68.7565805306348}};
      out.at(4) = L;
      break;

    case System::tuned_manual:
      A = Matrix{{0,                 0, 1, 0},
                 {0,                 0, 0, 1},
                 {47.2746736626568,  0, 0, 0},
                 {-1.34433823959577, 0, 0, 0}};
      out.at(0) = A;

      // B matrix
      B = Matrix{{0},
                 {0},
                 {0.0968725463390153},
                 {-0.00331057279509083}};
      out.at(1) = B;

      // C matrix
      C = Matrix{{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
      out.at(2) = C;

      // K matrix
      K = Matrix{{802.88, 0, 139.09, 784.99}};
      out.at(3) = K;

      L = Matrix{{10,                0,  1,  0},
                 {0,                 20, 0,  1},
                 {47.2746736626568,  0,  30, 0},
                 {-1.34433823959577, 0,  0,  68.7565805306348}};
      out.at(4) = L;
      break;

    case System::LQR:
      A = Matrix{{0,                 0, 1, 0},
                 {0,                 0, 0, 1},
                 {47.2746736626568,  0, 0, 0},
                 {-1.34433823959577, 0, 0, 0}};
      out.at(0) = A;

      // B matrix
      B = Matrix{{0},
                 {0},
                 {0.0968725463390153},
                 {-0.00331057279509083}};
      out.at(1) = B;

      // C matrix
      C = Matrix{{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
      out.at(2) = C;

      // K matrix
      K = Matrix{{991.909531865653, 0.930291450322719, 145.759105890912, 58.798408812102}};
      out.at(3) = K;

      L = Matrix{{1.0023446186431,     0,                   0.00999790502270166, 0},
                 {0,                   0.618055294598948,   0,                   0.00723641117238562},
                 {0.473109854821532,   0,                   1.00136453279657,    0},
                 {-0.0134538110133856, 0.00105579634750382, 0,                   0.618061483637312}};
      out.at(4) = L;
      break;

    case System::pole_placement_discrete:
      A = Matrix{{0,                 0, 1, 0},
                 {0,                 0, 0, 1},
                 {47.2746736626568,  0, 0, 0},
                 {-1.34433823959577, 0, 0, 0}};
      out.at(0) = A;

      // B matrix
      B = Matrix{{0},
                 {0},
                 {0.0968725463390153},
                 {-0.00331057279509083}};
      out.at(1) = B;

      // C matrix
      C = Matrix{{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
      out.at(2) = C;

      // K matrix
      K = Matrix{{958.097552156146, 0, 140.746653569888, 54.8485642096788}};
      out.at(3) = K;

      L = Matrix{{1.0023446186431,     0,                   0.00999790502270166, 0},
                 {0,                   0.618055294598948,   0,                   0.00723641117238562},
                 {0.473109854821532,   0,                   1.00136453279657,    0},
                 {-0.0134538110133856, 0.00105579634750382, 0,                   0.618061483637312}};
      out.at(4) = L;
      break;
  }
  return out;
}


