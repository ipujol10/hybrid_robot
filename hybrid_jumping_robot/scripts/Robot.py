#!/usr/bin/env python3
from IMU_robot import IMU
from Actuator_robot import Actuator
from Vel_robot import Vel
import time

class Robot:

    def __init__(self, name):
        self.name = name
        self.imu = IMU('someimuname')
        self.actuator = Actuator()
        self.velocity = Vel()
        self.imu.listener()

    def get_rpy(self):
        print(self.imu.get_rpy())

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
    time.sleep(1)
    while 1:
        r.get_rpy()
