#include "src/Hybrid_jumping_Robot.hpp"
//#include <Eigen/Dense>

int main(int argc, char **argv) {
  ros::init(argc, argv, "hybrid_jumping_robot");
  ros::NodeHandle nh;
//  Eigen::MatrixXd m(2, 2);
//  m(0,0) = 3;
//  m(1,0) = 2.5;
//  m(0,1) = -1;
//  m(1,1) = m(1,0) + m(0,1);
//  std::cout << m << std::endl;
  auto robot = Hybrid_jumping_Robot("hybrid_jumping_robot", -36, 0.075);
  ros::spin();
}