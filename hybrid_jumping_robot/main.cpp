#include "src/Hybrid_jumping_Robot.hpp"

int main(int argc, char **argv) {
  ros::init(argc, argv, "hybrid_jumping_robot");
  ros::NodeHandle nh;
  auto robot = Hybrid_jumping_Robot("hybrid_jumping_robot", -36, 0.075);
}