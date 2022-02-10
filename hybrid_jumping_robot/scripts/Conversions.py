#!/usr/bin/env python3
import tf
from math import pi
from geometry_msgs.msg import Quaternion


def quaternion_to_rpy(quaternion):
    if type(quaternion) == list or type(quaternion) == tuple:
        return tf.transformations.euler_from_quaternion(quaternion)
    elif type(quaternion) == Quaternion:
        return tf.transformations.euler_from_quaternion([quaternion.x, quaternion.y, quaternion.z, quaternion.w])


def angular_velocity_to_rpm(angular):
    return angular * 30 / pi


def angular_to_linear_velocity(angular, radius, rpm=True):
    if (not rpm):
        angular = angular_velocity_to_rpm(angular)
    return radius * angular


def rpm_to_angular(rpm):
    return rpm * pi / 30
