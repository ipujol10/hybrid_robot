#include "src/Hybrid_jumping_Robot.hpp"
//#include <acado/acado_toolkit.hpp>

int main(int argc, char **argv) {
  ros::init(argc, argv, "hybrid_jumping_robot");
  ros::NodeHandle nh;
//  ACADO::PIDcontroller pid(2, 1, 0.01);
  auto robot = Hybrid_jumping_Robot("hybrid_jumping_robot", -36, 0.075);
  ros::spin();
}