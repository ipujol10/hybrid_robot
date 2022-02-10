#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64, String
from Conversions import quaternion_to_rpy
import PID


class Stabilize:
    orientation = []

    def __init__(self, name, pid=(1, 0, 0), target=0, show: bool = False):
        rospy.init_node(name, anonymous=True)  # , log_level=rospy.DEBUG)
        rospy.Rate(5)
        (p, i, d) = pid
        # self.pid = PID.PID(p, i, d)
        # self.pid.SetPoint(target)
        # self.pid.setSampleTime(1)
        self.show = show

        self.subscribe()
        # PUBLISHERS
        self.send_vel = rospy.Publisher("/internal/stabilize/controller/velocity", Float64, queue_size=10)
        # PUBLISHERS

    def subscribe(self):
        rospy.Subscriber("/imu", Imu, self.imu_callback)

    def imu_callback(self, data: Imu):
        ori = data.orientation
        self.orientation = quaternion_to_rpy([ori.x, ori.y, ori.z, ori.w])
        (_, pitch, _) = self.orientation  # (roll, pitch, yaw)
        if self.show:
            self.show_orientation()
        # self.pid.update(pitch)
        # velocity = self.pid.output
        # msg = Float64(velocity)
        # self.send_vel.publish(msg)

    def show_orientation(self):
        rospy.loginfo("(roll, pitch, yaw) = ({}, {}, {})".format(self.orientation[0], self.orientation[1], self.orientation[2]))
        rospy.loginfo("Pitch = {}".format(self.orientation[1]))


if __name__ == "__main__":
    stable = Stabilize("pid", show=True)
    rospy.spin()
