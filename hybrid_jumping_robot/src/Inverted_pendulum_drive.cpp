//
// Created by woombat on 2/24/22.
//

#include "Inverted_pendulum_drive.hpp"
#include <cmath>

IPD::IPD(const std::string& name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd ,Float64 sampletime):
        pid(name, target, Kp, Ki, Kd, sampletime, ros::Time::now()), rate(100) {
    ros::NodeHandle nh;
//    inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1000);
    inverted_vel_pub = nh.advertise<std_msgs::Float64>(inverted_vel_connection, 1);
    inverted_pitch_sub = nh.subscribe(inverted_pitch_connection,1, &IPD::callbackPitch,this);

    pid.setWindup(20.0);
    ROS_ERROR("Inverted Pendulum Drive OK");

}
void IPD::callbackPitch(const std_msgs::Float64 &data){
    Pitch = data.data;
}


void IPD::loop() {
  while (ros::ok()) {
    std_msgs::Float64 data;
    auto velocity = pid.update(Pitch, ros::Time::now());
//    ROS_INFO_THROTTLE(0.5, "New velocity %f", velocity);
    data.data = velocity;
    inverted_vel_pub.publish(data);
    ros::spinOnce();
    rate.sleep();
//        ros::Rate loop_rate(100);
  }
}



int main(int argc, char **argv){
    ros::init(argc, argv,"Inverted_pendulum_drive");
    ros::NodeHandle nh;
    IPD ipd("pid", M_PI_2, 50, 0.001, 0.01, 1e-2);
    ipd.loop();
    return 0;
}