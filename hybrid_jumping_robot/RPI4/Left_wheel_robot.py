#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64
import math
import serial


class Left_wheel_robot:
    set_velocity = 0.0
    current_velocity = 0.0

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.sub_set_velocity = rospy.Subscriber('/HJC/Vel_robot/Set_velocity', Float64, self.set_velocity_cb)
        self.pub_current_velocity = rospy.Publisher('/HJC/Vel_robot/Current_velocity', Float64, queue_size=1)
        self.ser = serial.Serial('/dev/ttyAMA*****', baudrate=9600,
                                 parity=serial.PARITY_NONE,
                                 stopbits=serial.STOPBITS_ONE,
                                 bytesize=serial.EIGHTBITS
                                 )

    def loop(self):

        while not rospy.is_shutdown():
            if self.ser.in_waiting > 0:
                try:
                    data = self.ser.read()
                    print(data)
                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")

        self.ser.close()

    def set_velocity_cb(self, data):
        self.set_velocity = data.data
        if self.ser.writable():
            self.ser.write(self.set_velocity)

    def close(self):
        self.ser.close()


if __name__ == '__main__':
    left_wheel_robot = Left_wheel_robot('John')
    try:
        left_wheel_robot.loop()
    except rospy.ROSInterruptException:
        print("fail")
    print('finish')
