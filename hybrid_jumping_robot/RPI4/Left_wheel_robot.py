#!/usr/bin/env python
import time

import rospy
from std_msgs.msg import Float64
import math
import serial
import RPi.GPIO as GPIO
import time






class Left_wheel_robot:
    set_velocity = 0.0
    current_velocity = 0.0
    servoPIN = 17
    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.sub_set_velocity = rospy.Subscriber('/HJC/Vel_robot/Set_velocity', Float64, self.set_velocity_cb)
        self.pub_current_velocity = rospy.Publisher('/HJC/Vel_robot/Current_velocity', Float64, queue_size=1)
        # /dev/ttyAMA4 is on gpio pin 8 TX 9 RX pin on rpi is 24 & 21
        # /dev/ttyAMA0 is on gpio pin 14 TX 15 RX pi
        # https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf
        self.ser = serial.Serial('/dev/ttyAMA0', baudrate=115200,
                                 parity=serial.PARITY_NONE,
                                 stopbits=serial.STOPBITS_ONE,
                                 bytesize=serial.EIGHTBITS
                                 )
        self.ser.flush()
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.servoPIN, GPIO.OUT)

        self.p = GPIO.PWM(self.servoPIN, 50) # GPIO 17 for PWM with 50Hz
        self.p.start(2.5) # Initialization
    def loop(self):

        while not rospy.is_shutdown():
            if self.ser.in_waiting > 0:
                try:
                    data = self.ser.readline()

                    self.pub_current_velocity.publish(Float64(float(data)))
                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")
            self.rate.sleep()

        self.ser.close()

    def set_velocity_cb(self, data):
        self.set_velocity = data.data

        if self.ser.writable():
            self.ser.write(str(self.set_velocity)+'\n')


    def close(self):
        self.ser.close()


if __name__ == '__main__':
    left_wheel_robot = Left_wheel_robot('John')
    try:
        left_wheel_robot.loop()
    except rospy.ROSInterruptException:
        print("fail")
    print('finish')
