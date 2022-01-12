#!/usr/bin/env python3
import tf


def quaternion_to_rpy(quaternion):
    return tf.transformations.euler_from_quaternion(quaternion)
