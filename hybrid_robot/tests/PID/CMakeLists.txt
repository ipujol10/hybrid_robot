cmake_minimum_required(VERSION 3.0.2)
project(PID_Test)

set(CMAKE_CXX_STANDARD 17)

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

set(SOURCE_FILES Simple_control.cpp Mat.cpp PID_tests.cpp)
set(HEADER_FILES Simple_control.hpp Mat.hpp PID_tests.hpp)

find_library(ROBOT_LIBRARY Robot HINTS /home/ipujol/AAU/S10/catkin_ws/src/hybrid_robot/hybrid_jumping_robot/src)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
include_directories(../../src)
target_link_libraries(${PROJECT_NAME} ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} ${ROBOT_LIBRARY})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)