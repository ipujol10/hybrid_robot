#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64


class Vel:
    left_front_wheel_publisher = ''
    right_front_wheel_publisher = ''
    left_back_wheel_publisher = ''
    right_back_wheel_publisher = ''
    left_front_wheel_connection = '/hybrid_robotV0_2/front_left_wheel_joint_effort_controller/command'
    right_front_wheel_connection = '/hybrid_robotV0_2/front_right_wheel_joint_effort_controller/command'
    left_back_wheel_connection = '/hybrid_robotV0_2/back_left_wheel_joint_velocity_controller/command'
    right_back_wheel_connection = '/hybrid_robotV0_2/back_right_wheel_joint_velocity_controller/command'
    left_front_wheel_velocity = 0.0
    right_front_wheel_velocity = 0.0
    left_back_wheel_velocity = 0.0
    right_back_wheel_velocity = 0.0

    def __init__(self, name):
        # rospy.init_node(name, anonymous=True)
        rospy.Rate(5)
        self.left_front_wheel_publisher = rospy.Publisher(self.left_front_wheel_connection, Float64, queue_size=10)
        self.right_front_wheel_publisher = rospy.Publisher(self.right_front_wheel_connection, Float64, queue_size=10)
        self.left_back_wheel_publisher = rospy.Publisher(self.left_back_wheel_connection, Float64, queue_size=10)
        self.right_back_wheel_publisher = rospy.Publisher(self.right_back_wheel_connection, Float64, queue_size=10)
        rospy.Subscriber("/internal/stabilize/controller/velocity", Float64, self.velocity_callback)

    def set_left_front_wheel_velocity(self, vel):
        rate = rospy.Rate(10)  # 10hz
        self.left_front_wheel_publisher.publish(vel)
        rate.sleep()

    def set_right_front_wheel_velocity(self, vel):
        rate = rospy.Rate(10)  # 10hz
        self.right_front_wheel_publisher.publish(vel)
        rate.sleep()

    def set_left_back_wheel_velocity(self, vel):
        rate = rospy.Rate(10)  # 10hz
        self.left_back_wheel_publisher.publish(vel)
        rate.sleep()

    def set_right_back_wheel_velocity(self, vel):
        rate = rospy.Rate(10)  # 10hz
        self.right_back_wheel_publisher.publish(vel)
        rate.sleep()

    def set_back_wheel_velocity(self, vel):
        rate = rospy.Rate(10)  # 10hz
        self.left_back_wheel_publisher.publish(vel)
        self.right_back_wheel_publisher.publish(vel)
        rate.sleep()

    def set_front_wheel_velocity(self, vel):
        rate = rospy.Rate(10)  # 10hz
        self.left_front_wheel_publisher.publish(vel)
        self.right_front_wheel_publisher.publish(vel)
        rate.sleep()

    def velocity_callback(self, data: Float64):
        vel = data.data
        self.set_front_wheel_velocity(vel)
