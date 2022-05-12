#include "Inverted_pendulum_drive.hpp"
#include <cmath>

IPD::IPD(const std::string &name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd, Float64 sample_time, int state) :
    pid(name, target, Kp, Ki, Kd, sample_time, ros::Time::now()), rate(100), state(state) {
  ros::NodeHandle nh;
//    inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1000);
  inverted_vel_pub = nh.advertise<std_msgs::Float64>("/HJC/Vel_robot/Set_velocity", 1);
  inverted_pitch_sub = nh.subscribe("/HJC/IMU/Pitch", 1, &IPD::callbackPitch, this);
  state_sub = nh.subscribe("/HJC/State_machine/State", 1, &IPD::callbackState, this);
  if (state == -1) {
    active = true;
  } else {
    active = false;
  }

  pid.setWindup(20.0);
}

void IPD::callbackPitch(const std_msgs::Float64 &data) {
  Pitch = data.data;
}


void IPD::loop() {
  while (ros::ok()) {
    if (true) {
      std_msgs::Float64 data;
      auto velocity = pid.update(Pitch, ros::Time::now(), true, 70, -70);
      velocity = filter(velocity,old_velocity, 0.8);
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

Float64 IPD::filter(Float64 new_vel, Float64 old_vel, Float64 alpha) {
    auto res = (new_vel * (1-alpha) ) + (old_vel * alpha);
    old_velocity = new_vel;
    return res;
}
