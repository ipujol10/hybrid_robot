//
// Created by woombat on 2/24/22.
//

#include "State_machine.hpp"
#include <std_msgs/Int8.h>


State_machine::State_machine(): input("0"), state_change(true){

    ros::NodeHandle nh;
    vel_sub = nh.subscribe( "/HJC/Vel_robot/Current_velocity",1,&State_machine::callback_vel,this );
    imu_sub = nh.subscribe( "/HJC/IMU/Pitch",1,&State_machine::callback_pitch,this );
    state_machine_input = nh.subscribe("/HJC/State_machine/Input", 1, &State_machine::callback_input, this);
    state_pub = nh.advertise<std_msgs::Int8>("/HJC/State_machine/State", 10);
    ros::Rate loop_rate(280);
    ros::spinOnce();
    loop_rate.sleep();

    duration = ros::Duration(10);
    state_sel = 0;
    while(ros::ok()){
        ROS_ERROR_THROTTLE(0.5, "SM");
        // statemachine
        // keyboard input to get from state 0 to state 1
//        char input;
//        std::cin >> input;
        if (state_sel == 0 && input == "f"){
            state_sel = 1;
            state_change = true;
        }
        // velocity has to be reached to get from state 1 to state 2
        if(state_sel == 1 && Velocity <= -16.5){
            state_sel = 2;
            state_change = true;
        }
        // pitch has to above 0.7 and below 2.3 to go from state 2 to state 3
        if(state_sel == 2 && 0.7 < Pitch && Pitch < 2.3){
            state_sel = 3;
            state_change = true;
        }
        // when pitch of the robot has been between pi/2 +/-0.1 (1.57) and the robot has balanced for at least 10
        if(1.55 < Pitch < 1.59 ){

        }else{
            balancing_time = ros::Time();
        }
        if (state_sel == 3 && duration.toNSec() > balancing_time.toNSec() - ros::Time().toNSec()){
            state_sel = 4;
            state_change = true;
        }
        // when jump velocity is acquired JUMP
        if(state_sel == 4 && Velocity >= 6.5){
            state_sel = 5;
            state_change = true;
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
    msg.data = state;
    if (state_change) {
      switch (state) {
        case 0:
          ROS_INFO("Initial State");
          break;
        case 1:
          ROS_INFO("4 Wheel Drive Mode");
          break;
        case 2:
          ROS_INFO("4 Wheel Break Mode");
          break;
        case 3:
          ROS_INFO("2 Wheel Stabilizing");
          break;
        case 4:
          ROS_INFO("2 Wheel Drive");
          break;
        case 5:
          ROS_INFO("Jump");
          break;
        default:
          break;
      }
      state_change = false;
    }
    state_pub.publish(msg);
    ros::spinOnce();
}

void State_machine::callback_input(const std_msgs::String &data) {
  input = data.data;
}
