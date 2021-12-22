cmake_minimum_required(VERSION 3.0.2)
project(hybrid_jumping_robot)

find_package(catkin REQUIRED COMPONENTS
        rospy
        roscpp
        std_msgs
        gazebo_ros
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

catkin_package(
    DEPENDS
      gazebo_ros
)

include_directories(
        # include
        ${catkin_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)
