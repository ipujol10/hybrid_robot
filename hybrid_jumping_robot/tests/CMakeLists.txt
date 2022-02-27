cmake_minimum_required(VERSION 3.0.2)
project(Tests)

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

find_library(PID_TEST_LIBRARY PID_Test HINTS /home/ipujol/AAU/S10/catkin_ws/src/hybrid_robot/hybrid_jumping_robot/tests/PID)

add_executable(${PROJECT_NAME} Tests.cpp)
include_directories(PID)
add_subdirectory(PID)
target_link_libraries(${PROJECT_NAME} ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} PID_Test)
#link_libraries(${PROJECT_NAME} ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} ${PID_TEST_LIBRARY})
#link_libraries(${PROJECT_NAME} ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES})