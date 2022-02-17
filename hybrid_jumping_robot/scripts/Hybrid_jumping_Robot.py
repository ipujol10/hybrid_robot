#!/usr/bin/env python3
import time

from pynput import keyboard
import Robot
from math import pi
import os
import Conversions as con

import rospy
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64
from Conversions import quaternion_to_rpy
import Stabilize


class OperatedRobot:
    moving = False
    roll = ''
    pitch = ''
    now_velocity = 0

    def __init__(self, name, velocity, wheelradii):
        self.robot = Robot.Robot(name)
        self.wheelradii = wheelradii
        self.velocity = velocity
        self.orientation = []
        self.print_timer = time.perf_counter()
        self.start_time = time.perf_counter()
        self.subscribe()
        time.sleep(5)
        # self.use_keyboard()
        self.running_states()

    def use_keyboard(self):
        with keyboard.Listener(
                on_press=self.on_press) as listener:
            listener.join()

    def subscribe(self):
        rospy.Subscriber("/imu", Imu, self.imu_callback,queue_size=1)

    def imu_callback(self, data: Imu):
        self.orientation = quaternion_to_rpy(data.orientation)
        (self.roll, self.pitch, _) = self.orientation  # (roll, pitch, yaw)
        #print(self.pitch)

    def move_robot(self, vel):
        set_velocity = vel
        print(set_velocity)

        print('\n')
        if not self.moving:
            self.now_velocity = 0

        print(self.now_velocity)
        while set_velocity <= self.now_velocity:
            print('increaing speed')
            self.now_velocity -= 5
            self.robot.set_front_vel(self.now_velocity)

        self.robot.set_actuator_position(-0.0)

    def break_robot(self, vel):
        self.robot.set_actuator_position(0.00)
        self.robot.set_front_vel(vel)

    def increase_velocity(self):
        self.velocity += 1.0
        print("velocity is: {}".format(self.velocity))
        if self.moving:
            print('moving')
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
                print(f'\nVelocity {con.RpmToVel(con.RadToRpm(self.velocity), self.wheelradii)} cm/sec'
                      f'\n Rpm {con.RpmToVel(self.velocity, self.wheelradii)}'
                      f'\n input vel {self.velocity}')
                self.move_robot(-self.velocity)
                self.moving = True
            if key.char == 'x':
                self.moving = False
                print('\nbreak')
                print(f'\nVelocity {con.RpmToVel(con.RadToRpm(0.0), self.wheelradii)} cm/sec')
                self.break_robot(0.0)
            if key.char == '+':
                self.increase_velocity()
                print(f'\nVelocity {con.RpmToVel(con.RadToRpm(self.velocity), self.wheelradii)} cm/sec'
                      f'\n Rpm {con.RpmToVel(self.velocity, self.wheelradii)}')
            if key.char == '-':
                self.decrease_velocity()
                print(f'\nVelocity {con.RpmToVel(con.RadToRpm(self.velocity), self.wheelradii)} cm/sec'
                      f'\n Rpm {con.RpmToVel(self.velocity, self.wheelradii)}')
            if key.char == '0':
                print("\nexiting")
                os._exit(os.EX_OK)
        except:
            print(f"\nYou pressed control you moron")

    def running_states(self):
        cnt = 0
        while 1:
            while type(self.pitch) == float:
                try:
                    # Driving State
                    if self.pitch < 0.02 and 30 < time.perf_counter() - self.start_time:
                        print(f'pitch is {self.pitch}')
                        self.velocity = 36.0
                        print('\nDriving State')
                        print(f'\nVelocity {con.RpmToVel(con.RadToRpm(self.velocity), self.wheelradii)} cm/sec'
                              f'\n Rpm {con.RpmToVel(self.velocity, self.wheelradii)}')
                        self.move_robot(-self.velocity)
                        self.moving = True

                    # Breaking State
                    if self.pitch < 0.7 and self.velocity > 35.0 and 31 < time.perf_counter() - self.start_time:
                        self.moving = False
                        print('\nBreaking State')
                        print(f'\nVelocity {con.RpmToVel(con.RadToRpm(0.0), self.wheelradii)} cm/sec')
                        self.break_robot(0.0)
                        cnt += 1
                        self.start_time = time.perf_counter()
                    # Inverted pendulum State
                    while self.pitch > 0.7:
                        print('\nInverted pendulum State')
                        print(f'pitch is {self.pitch}')
                        stable = Stabilize.Stabilize("pid", (21.5, 0.01, 18.75))
                        #stable.update_pid(self.orientation)
                        while self.pitch > 0.7:
                            # print(f'pitch is {self.pitch}')
                            time.sleep(0.01)
                            print(f'orientation is {self.orientation} ')
                            self.velocity = stable.update_pid(self.orientation)
                            print(f'pid output {stable.velocity} forced output {self.velocity}')
                            if self.velocity > 0.0 or self.velocity < 0.0:
                                self.move_robot(-self.velocity)

                    if cnt > 1:
                        print("\nexiting")
                        os._exit(os.EX_OK)
                except:
                    print('initializing')


if __name__ == '__main__':
    r = OperatedRobot('hybrid_jumping_robot', 36.0, 0.075)
