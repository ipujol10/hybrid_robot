#include "IMU_robot.hpp"
#include <ros/ros.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "IMU_node");
    ros::NodeHandle nh;
    IMU imu;
}