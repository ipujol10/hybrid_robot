#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64
from geometry_msgs.msg import Vector3
import math
import serial
import time


class wheel_robot:
    set_velocity = 0.0
    current_velocity = 0.0
    velocity_left = 0.0
    velocity_right = 0.0
    #meassurea this
    base_withd = 0.232
    wheel_radii = 0.162/2

    vl = 0.0
    vr = 0.0

    x_pos = 0.0
    y_pos = 0.0
    theta_pos = 0.0



    def __init__(self, name):
        self.angle_left = 0.0
        self.angle_right = 0.0
        self.oldTime = time.time()
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.sub_set_velocity = rospy.Subscriber('/HJC/Vel_robot/Set_velocity', Float64, self.set_velocity_cb)
        self.pub_current_velocity = rospy.Publisher('/HJC/Vel_robot/Current_velocity', Float64, queue_size=1)
        self.pub_current_pos = rospy.Publisher('/HJC/Vel_robot/Current_pos', Vector3, queue_size=1)
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
                    data_arr_left = data_input_left.split(",")
                    self.velocity_left = -round(float(data_arr_left[0].split(":")[1]), 3)
                    angle_out_left = data_arr_left[1].split(":")
                    self.angle_left = angle_out_left[1].rstrip()

                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")

            if self.right_wheel_serial.in_waiting > 0:
                try:
                    data_input_right = self.right_wheel_serial.readline()
                    data_arr_right = data_input_right.split(",")
                    self.velocity_right = round(float(data_arr_right[0].split(":")[1]), 3)
                    angle_out_right = data_arr_right[1].split(":")
                    self.angle_right = angle_out_right[1].rstrip()

                except KeyboardInterrupt:
                    print("Exiting Program")
                except:
                    print("Error Occurs, Exiting Program")
            self.odom()
            vel = float(self.velocity_left) + float(self.velocity_right) * 0.5
            pos_msg = Vector3()
            pos_msg.x = self.x_pos
            pos_msg.y = self.y_pos
            pos_msg.z = self.theta_pos
            self.pub_current_pos.publish(pos_msg)
            self.pub_current_velocity.publish(float(self.rpmtovel(vel)))
            self.pub_left_wheel_pos.publish(float(self.angle_left))
            self.pub_right_wheel_pos.publish(float(self.angle_right))
            self.rate.sleep()
        self.left_wheel_serial.close()
        self.right_wheel_serial.close()
        self.serBreak.close()

    def set_velocity_cb(self, data):
        self.set_velocity = data.data

        if self.left_wheel_serial.writable():
            self.left_wheel_serial.write(str(self.set_velocity*200) + '\n')
        if self.right_wheel_serial.writable():
            self.right_wheel_serial.write(str(self.set_velocity*200) + '\n')
        if self.serBreak.writable():
            self.serBreak.write(str(int(self.set_velocity))+'\n')
            print(str(int(self.set_velocity)))

    def close(self):
        self.left_wheel_serial.close()
        self.right_wheel_serial.close()
        self.serBreak.close()


    def rpmtovel(self,rpm):
        v = ((math.pi * self.wheel_radii * rpm ) / 60.0) # meters a second
        v = v * (time.time()-self.oldTime ) #time
        return v

    ## not sure on this eq.
    def odom(self):
        pos = self.caldot()
        self.x_pos += round(pos['xdot'],4)
        self.y_pos += round(pos['ydot'],4)
        self.theta_pos += round(pos['thetadot'],2)
        rospy.loginfo_throttle(1, ("x pos is {}\t y pos is {}\t oriantation theta is {}").format(self.x_pos, self.y_pos, self.theta_pos))

    def caldot(self):
        self.calvrvrl()
        #xdot = (self.wheel_radii/2) * (self.vr + self.vl) * math.cos(self.theta_pos) # Think the reason why we got a longer distance was that we multiplied wheel_radii twice
        #ydot = (self.wheel_radii/2) * (self.vr + self.vl) * math.sin(self.theta_pos)
        xdot = (self.vr + self.vl) * math.cos(self.theta_pos)
        ydot = (self.vr + self.vl) * math.sin(self.theta_pos)
        #thetadot = (self.wheel_radii/self.base_withd) * (self.vr - self.vl)
        thetadot = (self.vr - self.vl) / self.base_withd
        return {'xdot': xdot, 'ydot': ydot, 'thetadot': thetadot}

    def calvrvrl(self):
        self.vr = round(self.rpmtovel(self.velocity_right),4)
        self.vl = round(self.rpmtovel(self.velocity_left),4)
        self.oldTime = time.time()
        file1 = open("myfile.txt", "a")  # append mode
        file1.write("{}\t{}\n".format(self.vr, self.vl))
        file1.close()


if __name__ == '__main__':
    wheel_robot = wheel_robot('odom')
    try:
        wheel_robot.loop()
    except rospy.ROSInterruptException:
        print("fail")
    print('finish')


