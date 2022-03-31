#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64
import math
import serial
import time


class wheel_robot:
    set_velocity = 0.0
    current_velocity = 0.0
    left_wheel_speed = 0.0
    right_wheel_speed = 0.0

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.sub_set_velocity = rospy.Subscriber('/HJC/Vel_robot/Set_velocity', Float64, self.set_velocity_cb)
        self.pub_current_velocity = rospy.Publisher('/HJC/Vel_robot/Current_velocity', Float64, queue_size=1)
        # /dev/ttyAMA4 is on gpio pin 8 TX 9 RX pin on rpi is 24 & 21
        # /dev/ttyAMA0 is on gpio pin 14 TX 15 RX pi
        # /dev/ttyAMA3 is on gpio pin 4 TX 5 RX pi
        # https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf
        self.left_serial_wheel = serial.Serial('/dev/ttyAMA0', baudrate=115200,
                                               parity=serial.PARITY_NONE,
                                               stopbits=serial.STOPBITS_ONE,
                                               bytesize=serial.EIGHTBITS
                                               )
        self.right_serial_wheel = serial.Serial('/dev/ttyAMA4', baudrate=115200,
                                                parity=serial.PARITY_NONE,
                                                stopbits=serial.STOPBITS_ONE,
                                                bytesize=serial.EIGHTBITS
                                                )
        #       40, DOWN, PWM0, SD4, -, SD1_DAT4, SPI2_MISO, TXD1
        # 41, DOWN, PWM1, SD5, TE0, SD1_DAT5, SPI2_MOSI, RXD1

        self.serBreak = serial.Serial('/dev/ttyAMA3', baudrate=115200,
                                 parity=serial.PARITY_NONE,
                                 stopbits=serial.STOPBITS_ONE,
                                 bytesize=serial.EIGHTBITS
                                 )
        self.right_serial_wheel.flush()
        self.left_serial_wheel.flush()
        self.serBreak.flush()




    def loop(self):
        while not rospy.is_shutdown():
            if self.left_serial_wheel.in_waiting > 0:
                try:
                    self.left_wheel_speed = float(self.left_serial_wheel.readline())
                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")
            if self.right_serial_wheel.in_waiting > 0:
                try:
                    self.right_wheel_speed = float(self.right_serial_wheel.readline())
                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")
            data = (self.left_wheel_speed + self.right_wheel_speed) * 0.5
            self.pub_current_velocity.publish(Float64(data))
            self.rate.sleep()
        self.left_serial_wheel.close()
        self.right_serial_wheel.close()

    def set_velocity_cb(self, data):
        self.set_velocity = data.data
        if self.left_serial_wheel.writable():
            self.left_serial_wheel.write(str(self.set_velocity) + '\n')
        if self.right_serial_wheel.writable():
            self.right_serial_wheel.write(str(self.set_velocity) + '\n')
        if self.serBreak.writable():
            self.serBreak.write(str(int(self.set_velocity))+'\n')
            print(str(int(self.set_velocity)))

    def close(self):
        self.left_serial_wheel.close()
        self.right_serial_wheel.close()
        self.serBreak.close()


if __name__ == '__main__':
    left_wheel_robot = wheel_robot('John')
    try:
        left_wheel_robot.loop()
    except rospy.ROSInterruptException:
        print("fail")
    print('finish')
