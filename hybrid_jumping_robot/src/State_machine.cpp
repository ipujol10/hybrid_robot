//
// Created by woombat on 2/24/22.
//

#include "State_machine.hpp"


State_machine::State_machine(){

    ros::NodeHandle nh;
    vel_sub = nh.subscribe( "/HJC/Vel_robot/Current_velocity",1,&State_machine::callback_vel,this );
    imu_sub = nh.subscribe( "/HJC/IMU/Pitch",1,&State_machine::callback_pitch,this );
    state_pub = nh.advertise<std_msgs::Int8>("/HJC/State_machine/State", 10);
    ros::Rate loop_rate(280);
    ros::spinOnce();
    loop_rate.sleep();

    duration = ros::Duration(10);
    state_sel = 0;
    while(ros::ok()){
        // statemachine
        // keyboard input to get from state 0 to state 1
        char input;
        std::cin >> input;
        if (state_sel == 0 && input == 'f'){
            state_sel = 1;
        }
        // velocity has to be reached to get from state 1 to state 2
        if(Velocity >= 16.5){
            state = 2;
        }
        // pitch has to above 0.7 and below 2.3 to go from state 2 to state 3
        if(0.7 < Pitch < 2.3){
            state_sel = 3;
        }
        // when pitch of the robot has been between pi/2 +/-0.1 (1.57)
        if(1.55 < Pitch < 1.59 ){

        }else{
            balancing_time = ros::Time();
        }
        if (duration.toNSec() > balancing_time.toNSec() - ros::Time().toNSec()){
            state_sel = 4;
        }
        // when jump velocity is acquired JUMP
        if(state_sel == 4 && Velocity >= 6.5){
            state_sel = 5;
        }
        State_machine::States(state_sel);
    }
}

void State_machine::callback_pitch(const std_msgs::Float64 &data){
    Pitch = data.data;
}
void State_machine::callback_vel(const std_msgs::Float64 &data){
    Velocity = data.data;
}

void State_machine::States(int state){
    std_msgs::Int8 msg;
    switch (state) {
        case 0:
            ROS_INFO("Initial State");
            msg.data = 0;
            state_pub.publish(msg);
            ros::spinOnce();
            break;
        case 1:
            ROS_INFO("4 Wheel Drive Mode");
            msg.data = 1;
            state_pub.publish(msg);
            ros::spinOnce();
            break;
        case 2:
            ROS_INFO("4 Wheel Break Mode");
            msg.data = 2;
            state_pub.publish(msg);
            ros::spinOnce();
            break;
        case 3:
            ROS_INFO("2 Wheel Stabilizing");
            msg.data = 2;
            state_pub.publish(msg);
            ros::spinOnce();
            break;
        case 4:
            ROS_INFO("2 Wheel Drive");
            msg.data = 2;
            state_pub.publish(msg);
            ros::spinOnce();
            break;
        case 5:
            ROS_INFO("Jump");
            msg.data = 2;
            state_pub.publish(msg);
            ros::spinOnce();
            break;
    }
}
