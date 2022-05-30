#!/usr/bin/env python3
from IMU_robot import IMU
from Actuator_robot import Actuator
from Vel_robot import Vel
import time


class Robot:

    def __init__(self, name):
        self.name = name
        self.imu = IMU('Hybrid_IMU')
        self.actuator = Actuator('Hybrid_actuator')
        self.velocity = Vel('Hybrid_velocity')
        self.imu.listener()

    def get_rpy(self):
        return self.imu.get_rpy()

    def get_vel(self):
        pass

    def set_back_vel(self, vel):
        self.velocity.set_back_wheel_velocity(vel)

    def set_front_vel(self, vel):
        self.velocity.set_front_wheel_velocity(vel)

    def get_actuator_position(self):
        pass

    def set_actuator_position(self, pos):
        self.actuator.set_extension_position(pos)


if __name__ == '__main__':
    r = Robot('test')
    time.sleep(1)
    while 1:
        r.get_rpy()
