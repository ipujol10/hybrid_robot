//
// Created by ipujol on 12/2/21.
//

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <string>

int main(int argc, char **argv) {
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate(10);

    std_msgs::String message;
    std::string str;
    std::cout << "Enter message: ";
    std::cin >> str;
    message.data = str;

    ROS_INFO("%s", message.data.c_str());
    chatter_pub.publish(message);

    std::cout << "ok" << std::endl;

    return 0;
}