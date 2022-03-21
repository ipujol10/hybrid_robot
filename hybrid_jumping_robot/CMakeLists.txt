cmake_minimum_required(VERSION 3.0.2)
project(hybrid_jumping_robot)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()


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

# CMake module(s) path
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR} )

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package( ACADO REQUIRED )

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
     ${ACADO_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(src)
include_directories(src)
#target_link_libraries(${PROJECT_NAME} Robot ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} Eigen3::Eigen)
target_link_libraries(${PROJECT_NAME} Robot ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} ${ACADO_SHARED_LIBRARIES})

#find_library(PID_TEST_LIBRARY PID_Test HINTS /home/ipujol/AAU/S10/catkin_ws/src/hybrid_robot/hybrid_jumping_robot/tests/PID)
#add_subdirectory(tests)
#add_executable(Tests tests/Tests.cpp)
#target_link_libraries(Tests ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} ${PID_TEST_LIBRARY} Robot)

add_subdirectory(nodes)
include_directories(nodes)
add_executable(IMU_node nodes/IMU_node.cpp)
target_link_libraries(IMU_node ${roscpp_LIBRARIES} Robot)

add_executable(Vel_node nodes/Vel_node.cpp)
target_link_libraries(Vel_node ${roscpp_LIBRARIES} Robot)

add_executable(IPD_node nodes/IPD_node.cpp)
target_link_libraries(IPD_node ${roscpp_LIBRARIES} Robot)

add_executable(Wheel_2_drive_node nodes/2_wheel_drive_node.cpp)
target_link_libraries(Wheel_2_drive_node ${roscpp_LIBRARIES} Robot)

add_executable(Wheel_2_stabilizing_node nodes/2_wheel_stabilizing_node.cpp)
target_link_libraries(Wheel_2_stabilizing_node ${roscpp_LIBRARIES} Robot)

add_executable(Wheel_4_break_node nodes/4_wheel_break_node.cpp)
target_link_libraries(Wheel_4_break_node ${roscpp_LIBRARIES} Robot)

add_executable(Wheel_4_drive_node nodes/4_wheel_drive_node.cpp)
target_link_libraries(Wheel_4_drive_node ${roscpp_LIBRARIES} Robot)

add_executable(Actuator_node nodes/Actuator_node.cpp)
target_link_libraries(Actuator_node ${roscpp_LIBRARIES} Robot)

add_executable(Jump_node nodes/Jump_node.cpp)
target_link_libraries(Jump_node ${roscpp_LIBRARIES} Robot)

add_executable(State_machine_node nodes/State_machine_node.cpp)
target_link_libraries(State_machine_node ${roscpp_LIBRARIES} Robot)