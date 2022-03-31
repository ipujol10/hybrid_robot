cmake_minimum_required(VERSION 3.0.2)
project(Robot)

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

set(HEADER_FILES IMU_robot.hpp Conversions.hpp Types.hpp Robot.hpp Actuator_robot.hpp Vel_robot.hpp Hybrid_jumping_Robot.hpp PID_controller.hpp Data.hpp Inverted_pendulum_drive.hpp State_machine.hpp LQR.hpp)
set(SOURCE_FILES IMU_robot.cpp Robot.cpp Conversions.cpp Actuator_robot.cpp Vel_robot.cpp Hybrid_jumping_Robot.cpp PID_controller.cpp Inverted_pendulum_drive.cpp State_machine.cpp LQR.cpp)


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${CATKIN_LIBRARIES} ${roscpp_LIBRARIES} ${ACADO_SHARED_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES LIKER_LANGUAGE CXX)