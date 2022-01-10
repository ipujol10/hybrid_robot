#!/usr/bin/env python3
from pynput import keyboard
import Robot


class OperatedRobot:

    def __init__(self, name, velocity):
        self.robot = Robot.Robot(name)
        self.velocity = velocity
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
        self.velocity += 1
        print("velocity is: {}".format(self.velocity))

    def decrease_velocity(self):
        self.velocity -= 1
        print("velocity is: {}".format(self.velocity))

    def on_press(self, key):
        try:
            print('Alphanumeric key pressed: {0} '.format(
                key.char))
        except AttributeError:
            print('special key pressed: {0}'.format(
                key))
        if key.char == 'w':
            print('move')
            self.move_robot(-self.velocity)
        if key.char == 'x':
            print('break')
            self.break_robot(0.0)
        if key.char == '+':
            self.increase_velocity()
        if key.char == '-':
            self.decrease_velocity()


if __name__ == '__main__':
    r = OperatedRobot('hybrid_jumping_robot', 10.0)
