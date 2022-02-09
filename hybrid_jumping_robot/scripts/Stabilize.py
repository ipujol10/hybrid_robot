#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64
from Conversions import quaternion_to_rpy
import PID


class Stabilize:
    orientation = []

    def __init__(self, name, pid=(1, 0, 0), target=0):
        rospy.init_node(name, anonymous=True)
        rospy.Rate(5)
        self.subscribe()
        # PUBLISHERS
        self.send_vel = rospy.Publisher("/internal/stabilize/controller/velocity", Float64, queue_size=10)
        # PUBLISHERS
        (p, i, d) = pid
        self.pid = PID.PID(p, i, d)
        self.pid.SetPoint(target)
        self.pid.setSampleTime(1)

    def subscribe(self):
        rospy.Subscriber("/imu", Imu, self.imu_callback)

    def imu_callback(self, data: Imu):
        self.orientation = quaternion_to_rpy(data.orientation)
        (_, pitch, _) = self.orientation  # (roll, pitch, yaw)
        self.pid.update(pitch)
        velocity = self.pid.output
        msg = Float64(velocity)
        self.send_vel.publish(msg)
