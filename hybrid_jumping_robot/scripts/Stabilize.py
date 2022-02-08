#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
from Conversions import quaternion_to_rpy
import PID


class Stabilize:
    orientation = []

    def __init__(self, name, pid=(1, 0, 0)):
        rospy.init_node(name, anonymous=True)
        rospy.Rate(5)
        self.subscribe()
        (p, i, d) = pid
        self.pid = PID.PID(p, i, d)

    def subscribe(self):
        rospy.Subscriber("/imu", Imu, self.imu_callback)

    def imu_callback(self, data: Imu):
        self.orientation = quaternion_to_rpy(data.orientation)
