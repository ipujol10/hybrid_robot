#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64
from Conversions import quaternion_to_rpy
import PID
import math


class Stabilize:
    orientation = []

    def __init__(self, name, pid=(1, 0, 0), target=math.pi / 2):
        rospy.init_node(name, anonymous=True)  # , log_level=rospy.DEBUG)
        rospy.Rate(5)
        (p, i, d) = pid
        self.pid = PID.PID(p, i, d)
        self.pid.SetPoint = target
        self.pid.setSampleTime(1)

        self.subscribe()
        # PUBLISHERS
        self.send_vel = rospy.Publisher("/internal/stabilize/controller/velocity", Float64, queue_size=10)
        # PUBLISHERS

    def subscribe(self):
        rospy.Subscriber("/imu", Imu, self.imu_callback)

    def imu_callback(self, data: Imu):
        self.orientation = quaternion_to_rpy(data.orientation)
        (_, pitch, _) = self.orientation  # (roll, pitch, yaw)
        self.pid.update(pitch)
        velocity = self.pid.output
        rospy.loginfo(velocity)
        msg = Float64(velocity)
        self.send_vel.publish(msg)


if __name__ == "__main__":
    stable = Stabilize("pid", (21.5, 0.01, 18.75))
    rospy.spin()
