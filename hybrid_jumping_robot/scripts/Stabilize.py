#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64
from Conversions import quaternion_to_rpy, get_correct_pitch
import PID
import math


class Stabilize:
    orientation = []
    velocity = ''

    def __init__(self, name, pid=(1, 0, 0), target=math.pi / 2):
        # rospy.init_node(name, anonymous=True)  # , log_level=rospy.DEBUG)
        # rospy.Rate(5)
        (p, i, d) = pid
        self.pid = PID.PID(p, i, d)
        self.pid.SetPoint = target
        self.pid.setSampleTime(0.05)

    # self.subscribe()
    # PUBLISHERS
    # self.send_vel = rospy.Publisher("/internal/stabilize/controller/velocity", Float64, queue_size=10)
    # self.send_pitch = rospy.Publisher("/internal/stabilize/controller/pitch", Float64, queue_size=10)
    # PUBLISHERS

    def update_pid(self, orientation):
        self.orientation = orientation
        (roll, pitch, _) = self.orientation  # (roll, pitch, yaw)
        # rospy.loginfo(pitch)
        # pitch = get_correct_pitch(pitch, roll)
        # rospy.loginfo("Roll: {: 7f} - Pitch: {: 7f}".format(roll, pitch))
        # self.send_pitch.publish(Float64(pitch))
        self.pid.update(pitch)
        self.velocity = -self.pid.output
        velocity = self.velocity
        if velocity > 20:
            velocity = 20
        if velocity < -20:
            velocity = -20
        return velocity
        # rospy.loginfo(velocity)
        # self.send_vel.publish(Float64(self.velocity))


'''
    def subscribe(self):
        rospy.Subscriber("/imu", Imu, self.imu_callback)

    def imu_callback(self, data: Imu):
        self.orientation = quaternion_to_rpy(data.orientation)
        (roll, pitch, _) = self.orientation  # (roll, pitch, yaw)
        # rospy.loginfo(pitch)
        pitch = get_correct_pitch(pitch, roll)
        # rospy.loginfo("Roll: {: 7f} - Pitch: {: 7f}".format(roll, pitch))
        self.send_pitch.publish(Float64(pitch))
        self.pid.update(pitch)
        self.velocity = self.pid.output
        # rospy.loginfo(velocity)
        self.send_vel.publish(Float64(self.velocity))
'''

if __name__ == "__main__":
    stable = Stabilize("pid", (21.5, 0.01, 18.75))
    rospy.spin()
