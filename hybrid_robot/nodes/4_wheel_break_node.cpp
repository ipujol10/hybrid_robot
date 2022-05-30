#include <ros/ros.h>
#include "std_msgs/Int8.h"
#include "std_msgs/Float64.h"
int state;

void callback(const std_msgs::Int8 &data){
    state = data.data;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "4_wheel_break_node");
    ros::NodeHandle nh;
    ros::Subscriber state_sub = nh.subscribe("/HJC/State_machine/State", 1, callback);
    ros::Publisher vel_pub = nh.advertise<std_msgs::Float64>("/HJC/Vel_robot/Set_velocity",10);
    ros::Rate loop_rate(280);
    ros::spinOnce();
    loop_rate.sleep();
    while(ros::ok()){
        if(state == 2){
            std_msgs::Float64 data;
            data.data = 0.0;
            vel_pub.publish(data);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }

}