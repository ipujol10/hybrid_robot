#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64
import math
import serial
import time


class Left_wheel_robot:
    set_velocity = 0.0
    current_velocity = 0.0

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.sub_set_velocity = rospy.Subscriber('/HJC/Vel_robot/Set_velocity', Float64, self.set_velocity_cb)
        self.pub_current_velocity = rospy.Publisher('/HJC/Vel_robot/Current_velocity', Float64, queue_size=1)
        self.pub_left_wheel_pos = rospy.Publisher('/HJC/Vel_robot/Left_wheel_pos', Float64, queue_size=1)
        self.pub_right_wheel_pos = rospy.Publisher('/HJC/Vel_robot/Right_wheel_pos', Float64, queue_size=1)
        # /dev/ttyAMA4 is on gpio pin 8 TX 9 RX pin on rpi is 24 & 21
        # /dev/ttyAMA0 is on gpio pin 14 TX 15 RX pi
        # /dev/ttyAMA3 is on gpio pin 4 TX 5 RX pi
        # https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf
        self.left_wheel_serial = serial.Serial('/dev/ttyAMA0', baudrate=115200,
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

        self.right_wheel_serial = serial.Serial('/dev/ttyAMA4', baudrate=115200,
                                                parity=serial.PARITY_NONE,
                                                stopbits=serial.STOPBITS_ONE,
                                                bytesize=serial.EIGHTBITS
                                                )
        self.left_wheel_serial.flush()
        self.right_wheel_serial.flush()
        self.serBreak.flush()






    def loop(self):
        data_left = 1
        data_right = 1
        angle_left = 1
        angle_right = 1
        while not rospy.is_shutdown():
            if self.left_wheel_serial.in_waiting > 0:
                try:
                    data_input_left = self.left_wheel_serial.readline()
                    #print(data_input_left)
                    data_arr_left = data_input_left.split(",")
                    data_left = data_arr_left[0].split(":")[1]
                    angle_out_left = data_arr_left[1].split(":")
                    angle_left = angle_out_left[1].rstrip()
                    #print("angle: {} rpm: {}".format(angle_left, data_left))
                    #print("data left has type:{} value is {}".format(type(data_left),data_left))
                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")

            if self.right_wheel_serial.in_waiting > 0:
                try:
                    data_input_right = self.right_wheel_serial.readline()
                    data_arr_right = data_input_right.split(",")
                    data_right = data_arr_right[0].split(":")[1]
                    angle_out_right = data_arr_right[1].split(":")
                    angle_right = angle_out_right[1].rstrip()

                    #print("data right has type:{} value is {}".format(type(data_right),data_right))


                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")

            data = float(data_left) + float(data_right) * 0.5
            self.pub_current_velocity.publish(Float64(float(data)))
            self.pub_left_wheel_pos.publish(Float64(float(angle_left)))
            self.pub_right_wheel_pos.publish(Float64(float(angle_right)))
            self.rate.sleep()
        self.left_wheel_serial.close()
        self.right_wheel_serial.close()

    def set_velocity_cb(self, data):
        self.set_velocity = data.data

        if self.left_wheel_serial.writable():
            self.left_wheel_serial.write(str(self.set_velocity) + '\n')
        if self.right_wheel_serial.writable():
            self.right_wheel_serial.write(str(self.set_velocity) + '\n')
        if self.serBreak.writable():
            self.serBreak.write(str(int(self.set_velocity))+'\n')
            print(str(int(self.set_velocity)))

    def close(self):
        self.left_wheel_serial.close()
        self.right_wheel_serial.close()
        self.serBreak.close()


if __name__ == '__main__':
    left_wheel_robot = Left_wheel_robot('John')
    try:
        left_wheel_robot.loop()
    except rospy.ROSInterruptException:
        print("fail")
    print('finish')


