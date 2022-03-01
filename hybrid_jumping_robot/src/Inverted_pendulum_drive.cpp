#include "Inverted_pendulum_drive.hpp"

IPD::IPD(int argc, char **argv, std::string name, Float64 target, Float64 Kp, Float64 Ki, Float64 Kd ,Float64 sampletime){

    ros::init(argc, argv,"Inverted_pendulum_drive");
    ros::NodeHandle nh;
    ros::Publisher inverted_vel_pub = nh.advertise<std_msgs::Float64>("/HJC/InvertedPendulumNode/vel", 1000);
    ros::Subscriber inverted_pitch_sub = nh.subscribe("/HJC/Robot/angle",1, &IPD::callbackPitch,this);

    PID pid = PID(name,target,Kp,Ki,Kd,sampletime,ros::Time());
    pid.setWindup(20.0);
    while(ros::ok()){

        std_msgs::Float64 data;
        data.data = pid.update(Pitch,ros::Time());

        inverted_vel_pub.publish(data);
        ros::spinOnce();
        ros::Rate loop_rate(100);
    }

}
void IPD::callbackPitch(const std_msgs::Float64 &data){

    Pitch = data.data;
}




int main(int argc, char **argv){
    IPD(argc, argv,"pid",M_PI/2,0.2,0.001,0.01,0.5);
    return 0;
}