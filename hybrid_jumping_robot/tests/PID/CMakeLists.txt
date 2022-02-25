cmake_minimum_required(VERSION 3.0.2)
project(PID_Test)

find_package(catkin REQUIRED COMPONENTS
    rospy
    roscpp
    std_msgs
    sensor_msgs
    gazebo_ros
    controller_manager
    joint_state_controller
    robot_state_publisher
    message_generation
    )

find_package(gazebo REQUIRED)

set(SOURCE_FILES PID_test.cpp Mat.cpp)
set(HEADER_FILES PID_test.hpp Mat.hpp)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LIKER_LANGUAGE CXX)