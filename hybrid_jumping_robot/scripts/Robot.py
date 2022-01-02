#!/usr/bin/env python3
from IMU_robot import IMU
from Actuator_robot import Actuator
from Vel_robot import Vel


class Robot:

    def __init__(self, name):
        self.name = name
        self.imu = IMU()
        self.actuator = Actuator()
        self.velocity = Vel()

    def get_rpy(self):
        pass

    def get_vel(self):
        pass

    def set_vel(self):
        pass

    def get_actuator_position(self):
        pass

    def set_actuator_position(self):
        pass


if __name__ == '__main__':
    r = Robot('test')
