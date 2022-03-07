#!/usr/bin/env python
import time

import rospy
from std_msgs.msg import Float64
import MPU9250
import math

class IMU:

    acc = 0.0
    gyro = 0.0
    mag = 0.0
    temp = 0.0
    oldPitch = 0.0
    oldTime = 0

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.pubPitch = rospy.Publisher('/HJC/IMU/Pitch', Float64, queue_size=1)
        self.pubAngVel = rospy.Publisher('/HJC/IMU/AngularVelocity', Float64, queue_size=1)
        self.mpu = MPU9250.MPU9250()
        self.mpu.configMPU9250(MPU9250.GFS_250, MPU9250.AFS_16G)
        self.mpu.configAK8963(MPU9250.AK8963_BIT_14, 1)

    def loop(self):
        while not rospy.is_shutdown():
            self.rate.sleep()
            if self.mpu.checkDataReady():
                self.acc = self.mpu.readAccel()
                self.gyro = self.mpu.readGyro()
                self.mag = self.mpu.readMagnet()
                self.temp = self.mpu.readTemperature()
                roll_pitch = self.calculateOriantation(self.acc)
                self.pubPitch.publish(Float64(roll_pitch['pitch']))
                rospy.loginfo_throttle(1, roll_pitch['pitch'])
                self.pubAngVel.publish(Float64(self.calculateAngularVelocity(roll_pitch['pitch'], rospy.get_rostime())))

    def calculateOriantation(self, acc):
        accelX = acc['x']
        accelY = acc['y']
        accelZ = acc['z']
        pitch = 180 * math.atan2(accelX, math.sqrt(accelY*accelY + accelZ*accelZ))/math.pi
        roll = 180 * math.atan2(accelY, math.sqrt(accelX*accelX + accelZ*accelZ))/math.pi
        return {"pitch": pitch, "roll": roll}


    def calculateAngularVelocity(self,pitch,now):
        pitch - self.oldPitch / now.secs - self.oldTime
        self.oldTime = now.secs
        self.oldPitch = pitch
        return {"pitchvel": pitch}



if __name__ == '__main__':
    imu = IMU('testIMU')
    try:
        imu.loop()
    except rospy.ROSInterruptException:
       print("fail")


