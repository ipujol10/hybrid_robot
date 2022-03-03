#include "IMU_robot.hpp"

IMU::IMU(): loop_rate(280) {
    sub = nh.subscribe("/imu", 1, &IMU::callback, this);
    pub_angle = nh.advertise<std_msgs::Float64>("/HJC/IMU/Pitch", 10);
    ROS_ERROR("IMU OK");
}

void IMU::callback(const sensor_msgs::Imu &data) {
  quaternion = data.orientation;
  angular_velocity = data.angular_velocity;
  linear_acceleration = data.linear_acceleration;
}

void IMU::loop() {
  while(ros::ok()){
    RPY rpy = conv::quaternion_to_rpy(quaternion);
    Float64 angle = conv::get_correct_pitch(rpy.pitch,rpy.roll);
    std_msgs::Float64 msg;
    msg.data = angle;
    pub_angle.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
