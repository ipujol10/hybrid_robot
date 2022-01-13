#!/usr/bin/env python3
import tf
from math import pi


def quaternion_to_rpy(quaternion):
    return tf.transformations.euler_from_quaternion(quaternion)


def angular_velocity_to_rpm(angular):
    return angular * 30 / pi


def angular_to_linear_velocity(angular, radius, rpm=True):
    if (not rpm):
        angular = angular_velocity_to_rpm(angular)
    return radius * angular


def rpm_to_angular(rpm):
    return rpm * pi / 30
