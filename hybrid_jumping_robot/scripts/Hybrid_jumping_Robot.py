#!/usr/bin/env python3
from pynput import keyboard
import Robot
from math import pi
import os
import Conversions as con




class OperatedRobot:
    moving = False

    def __init__(self, name, velocity,wheelradii):
        self.robot = Robot.Robot(name)
        self.wheelradii = wheelradii
        self.velocity = velocity
        with keyboard.Listener(
                on_press=self.on_press) as listener:
            listener.join()

    def move_robot(self, vel):
        set_velocity = vel
        print(set_velocity)

        print('\n')
        now_velocity = 0
        print(now_velocity)
        while set_velocity <= now_velocity:
            print('increaing speed')
            now_velocity -= 5
            self.robot.set_front_vel(now_velocity)

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
                print(f'\nVelocity { con.RpmToVel(con.RadToRpm(self.velocity),self.wheelradii)} cm/sec'
                      f'\n Rpm {con.RpmToVel(self.velocity,self.wheelradii)}')
                self.move_robot(-self.velocity)
            if key.char == 'x':
                self.moving = False
                print('\nbreak')
                self.break_robot(self.velocity / 50)
                print(f'\nVelocity { con.RpmToVel(con.RadToRpm(0.0),self.wheelradii)} cm/sec')
                self.break_robot(0.0)
            if key.char == '+':
                self.increase_velocity()
                print(f'\nVelocity { con.RpmToVel(con.RadToRpm(self.velocity),self.wheelradii)} cm/sec'
                      f'\n Rpm {con.RpmToVel(self.velocity,self.wheelradii)}')
            if key.char == '-':
                self.decrease_velocity()
                print(f'\nVelocity { con.RpmToVel(con.RadToRpm(self.velocity),self.wheelradii)} cm/sec'
                      f'\n Rpm {con.RpmToVel(self.velocity,self.wheelradii)}')
            if key.char == '0':
                print("\nexiting")
                os._exit(os.EX_OK)
        except:
            print(f"\nYou pressed control you moron")


if __name__ == '__main__':
    r = OperatedRobot('hybrid_jumping_robot', 0.0, 0.075)
