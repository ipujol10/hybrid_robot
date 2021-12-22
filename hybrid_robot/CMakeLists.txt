cmake_minimum_required(VERSION 3.12)
project(hybrid_robot)

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

add_executable(Trial trial.cpp)

target_link_libraries(Trial ${catkin_LIBRARIES})

catkin_install_python(PROGRAMS trial.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)