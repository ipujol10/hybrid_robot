#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64


class Actuator:
    extension_publisher = ''
    extension_connection = '/hybrid_robotV0_2/extension_base_joint_position_controller/command'
    extension_position = 0.0

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        rospy.Rate(5)
        self.extension_publisher = rospy.Publisher(self.extension_connection, Float64, queue_size=10)

    def set_extension_position(self, pos):
        rate = rospy.Rate(10)  # 10hz
        self.extension_publisher.publish(pos)
        rate.sleep()
