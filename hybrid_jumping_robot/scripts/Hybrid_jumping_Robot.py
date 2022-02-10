#!/usr/bin/env python3
from pynput import keyboard
import Robot
from math import pi
import os


def RadToRpm(radians):
    return (radians / (2 * pi)) * 60


def RpmToRad(rpm):
    return rpm / 60 * 2 * pi


def RpmToVel(rpm, radii):
    return 2 * pi * radii * rpm


class OperatedRobot:
    moving = False

    def __init__(self, name, velocity):
        self.robot = Robot.Robot(name)
        self.velocity = velocity
        with keyboard.Listener(
                on_press=self.on_press) as listener:
            listener.join()

    def move_robot(self, vel):
        self.robot.set_front_vel(vel)
        self.robot.set_actuator_position(-0.0)

    def break_robot(self, vel):
        self.robot.set_actuator_position(0.00)
        self.robot.set_front_vel(vel)

    def increase_velocity(self):
        self.velocity += 1.0
        print("velocity is: {}".format(self.velocity))
        if self.moving:
            print('moveing')
            self.move_robot(-self.velocity)

    def decrease_velocity(self):
        self.velocity -= 1.0
        print("velocity is: {}".format(self.velocity))
        if self.moving:
            self.move_robot(-self.velocity)

    # 6.282 sek a rotation
    def on_press(self, key):
        try:
            if key.char == 'w':
                print('\nmove')
                self.moving = True
                print(f'\nVelocity { RpmToVel(RadToRpm(self.velocity),0.075)} cm/minute')
                self.move_robot(-self.velocity)
            if key.char == 'x':
                self.moving = False
                print('\nbreak')
                self.break_robot(self.velocity / 50)
                print(f'\nVelocity { RpmToVel(RadToRpm(0.0),0.075)} cm/minute')
                self.break_robot(0.0)
            if key.char == '+':
                self.increase_velocity()
                print(f'\nVelocity { RpmToVel(RadToRpm(self.velocity),0.075)} cm/minute')
            if key.char == '-':
                self.decrease_velocity()
                print(f'\nVelocity { RpmToVel(RadToRpm(self.velocity),0.075)} cm/minute')
            if key.char == '0':
                print("\nexiting")
                os._exit(os.EX_OK)
        except:
            print(f"\nYou pressed control you moron")


if __name__ == '__main__':
    r = OperatedRobot('hybrid_jumping_robot', 0.0)
