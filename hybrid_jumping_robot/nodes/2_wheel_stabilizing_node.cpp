#include "Inverted_pendulum_drive.hpp"
#include <ros/ros.h>
#include <std_msgs/Int8.h>

int state;

void callback(const std_msgs::Int8 &data) {
  state = data.data;
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "TwoWS_node");
  ros::NodeHandle nh;
  ros::Subscriber state_sub = nh.subscribe("/HJC/State_machine/State", 1, callback);
  ros::Rate loop_rate(280);
  auto matrix = IPD::get_matrix(System::k_manual);
  Matrix target{{1.49},
                {0},
                {0},
                {0}};
  Matrix initial_state{{0},
                       {0},
                       {0},
                       {0}};
  IPD ipd(target, matrix.at(0), matrix.at(1), matrix.at(2), Matrix{{0}}, matrix.at(3), initial_state, 200, -1,
          matrix.at(4));
//  IPD ipd("stabilizing", M_PI_2, 27, 0, 5.5e-1, 9.9e-3, 3);

  ipd.loop();
}