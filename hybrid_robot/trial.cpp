//
// Created by ipujol on 12/2/21.
//

#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "trial");

  ros::NodeHandle n;

  ros::Publisher publisher = n.advertise<std_msgs::Float64>("/hybrid_robot/prismatic_controller/command", 100);

  ros::Rate loop_rate(10);

  bool cont = true;
  double c;
  while (cont) {
    std::cout << "input: ";
    std::cin >> c;
    if (c > 0 || c < -0.9) {
      ROS_INFO("Invalid input");
      ROS_INFO("-0.9 <= input <= 0");
    }
    else cont = false;
  }

  ROS_INFO("Going to publish");
  loop_rate.sleep();
  std_msgs::Float64 msg;
  msg.data = c;
  publisher.publish(msg);
  ROS_INFO("Published: %f", c);

  return 0;
}