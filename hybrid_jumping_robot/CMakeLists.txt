cmake_minimum_required(VERSION 3.0.2)
project(hybrid_jumping_robot)

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

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)


catkin_package(
    DEPENDS
        gazebo_ros
        controller_manager
        joint_state_controller
        robot_state_publisher
        CATKIN_DEPENDS rospy std_msgs sensor_msgs
)

include_directories(
        # include
        ${catkin_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)
