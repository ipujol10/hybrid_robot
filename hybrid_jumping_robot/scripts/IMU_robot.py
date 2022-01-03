#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from sensor_msgs.msg import Imu
import tf


def quaternion_to_rpy(quaternion):
    return tf.transformations.euler_from_quaternion(quaternion)


class IMU:

    quaternion = []
    quaternion_covariance = []
    angular_velocity = []
    angular_velocity_covariance = []
    linear_acceleration = []
    linear_acceleration_covariance = []
    rate = 10

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        rospy.Rate(5)

    def listener(self):
        rospy.Subscriber("/imu", Imu, self.callback)


    def callback(self, data):
        self.quaternion = data.orientation
        self.quaternion_covariance = data.orientation_covariance
        self.angular_velocity = data.angular_velocity
        self.angular_velocity_covariance = data.angular_velocity_covariance
        self.linear_acceleration = data.linear_acceleration
        self.linear_acceleration_covariance = data.linear_acceleration_covariance
        print('callbacks')

    def get_quaternion(self):
        return self.quaternion

    def get_quaternion_covariance(self):
        return self.quaternion_covariance

    def get_rpy(self):
        q = [self.quaternion.x, self.quaternion.y, self.quaternion.z, self.quaternion.w]
        return quaternion_to_rpy(q)

    def get_rpy_covariance(self):
        return self.quaternion_covariance[0:3]

    def get_angular_velocity(self):
        return self.angular_velocity

    def get_angular_velocity_covariance(self):
        return self.angular_velocity_covariance

    def get_linear_acceleration(self):
        return self.linear_acceleration

    def get_linear_acceleration_covariance(self):
        return self.linear_acceleration_covariance


if __name__ == '__main__':
    imu = IMU('test')
    imu.listener()
