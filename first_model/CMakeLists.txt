cmake_minimum_required(VERSION 3.12)
project(first_world)

find_package(catkin REQUIRED COMPONENTS
        rospy
        roscpp
        std_msgs
)

catkin_package(

)

include_directories(
        # include
        ${catkin_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)