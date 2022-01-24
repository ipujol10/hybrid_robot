#!/usr/bin/env python3
from pynput import keyboard
import Robot
from math import pi

class OperatedRobot:

    moving = False
    def __init__(self, name, velocity):
        self.robot = Robot.Robot(name)
        self.velocity = (velocity * 2 * pi) / 60  # rotations per minute
        with keyboard.Listener(
                on_press=self.on_press) as listener:
            listener.join()

    def move_robot(self, vel):
        self.robot.set_front_vel(vel)
        self.robot.set_actuator_position(0.04)

    def break_robot(self, vel):
        self.robot.set_front_vel(vel)
        self.robot.set_actuator_position(0.04)

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

    def on_press(self, key):

        print('Alphanumeric key pressed: {0} '.format(
            key.char))

        if key.char == 'w':
            print('move')
            self.moving = True
            self.move_robot(-self.velocity)
        if key.char == 'x':
            self.moving = False
            print('break')
            self.break_robot(0.0)
        if key.char == '+':
            self.increase_velocity()
        if key.char == '-':
            self.decrease_velocity()


if __name__ == '__main__':
    r = OperatedRobot('hybrid_jumping_robot', 10.0)
