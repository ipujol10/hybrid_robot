#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64
from registers import *
from mpu9250 import MPU9250
import math
import time
from madgwick import *
import numpy

class IMU:
    acc = 0.0
    gyro = 0.0
    mag = 0.0
    temp = 0.0
    oldPitch = 0.0
    oldRoll = 0.0
    oldTime = 0

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(500)
        self.pubPitch = rospy.Publisher('/HJC/IMU/Pitch', Float64, queue_size=1)
        self.pubAngVel = rospy.Publisher('/HJC/IMU/AngularVelocity', Float64, queue_size=1)
        self.mpu = MPU9250( address_ak=AK8963_ADDRESS,
                            address_mpu_master=MPU9050_ADDRESS_68, # Master has 0x68 Address
                            address_mpu_slave=MPU9050_ADDRESS_68, # Slave has 0x68 Address
                            bus=1,
                            gfs=GFS_500,
                            afs=AFS_4G,
                            mfs=AK8963_BIT_14,
                            mode=AK8963_MODE_C100HZ)

        self.mpu.configure() # Apply the settings to the registers.
        self.mpu.calibrateMPU6500() # Calibrate sensors
        self.mpu.configure() # The calibration function resets the sensors, so you need to reconfigure them
        #self.madgwick_angles = MadgwickAHRS()
        self.oldTime = time.time()

    def loop(self):
        while not rospy.is_shutdown():
            self.acc = self.mpu.readAccelerometerMaster()
            self.gyro = self.mpu.readGyroscopeMaster()
            self.mag = self.mpu.readMagnetometerMaster()
            self.temp = self.mpu.readTemperatureMaster()
            #self.madgwick_angles.update(self.gyro,self.acc,self.mag)
            #rpy = numpy.ndarray
            #rpy = self.madgwick_angles.quaternion.q()
            #print("rpy: ", rpy)
            roll_pitch = self.calculateOriantation(self.acc)
            self.pubPitch.publish(Float64(roll_pitch['pitch']))
            rospy.loginfo_throttle(1,"pitch is {} and roll is {}".format( roll_pitch['pitch'], roll_pitch['roll']))
            self.pubAngVel.publish(Float64(self.calculateAngularVelocity(roll_pitch['pitch'], rospy.get_rostime())))
            self.rate.sleep()
        time.sleep(1)

    def calculateOriantation(self, acc):
        accelX = acc[0]
        accelY = acc[1]
        accelZ = acc[2]
        #rospy.loginfo_throttle(1,"x is {} and y is {} z is {}".format( accelX, accelY, accelZ))
        pitch = round(math.atan2(accelX, math.sqrt(accelY * accelY + accelZ * accelZ)), 3)
        roll = round(math.atan2(accelY, math.sqrt(accelX * accelX + accelZ * accelZ)),3)
        if accelZ < 0:
            pitch = math.pi-pitch
        pitch = self.notch(pitch, self.oldPitch)
        roll = self.notch(roll, self.oldRoll)
        self.oldPitch = pitch
        self.oldRoll = roll
        return {"pitch": pitch, "roll": roll}

    def calculateAngularVelocity(self, pitch, now):
        (pitch - self.oldPitch) / (time.time() - self.oldTime)
        self.oldTime = now.secs
        self.oldPitch = pitch
        return pitch

    def notch(self,new,old,alpha = 0.3):
        return new * alpha + (1-alpha) * old

if __name__ == '__main__':
    imu = IMU('testIMU')
    try:
        imu.loop()
    except rospy.ROSInterruptException:
        print("fail")
