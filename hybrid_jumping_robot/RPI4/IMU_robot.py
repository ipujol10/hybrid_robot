#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
import MPU9250


class IMU:

    def __init__(self, name):
        rospy.init_node(name, anonymous=True)
        self.rate = rospy.Rate(280)
        self.pubPitch = rospy.Publisher('/HJC/IMU/Pitch', Imu)
        self.pubAngVel = rospy.Publisher('/HJC/IMU/AngularVelocity', Imu)
        self.mpu = MPU9250.MPU9250()
        self.mpu.configMPU9250(MPU9250.GFS_250, MPU9250.AFS_16G)
        self.mpu.configAK8963(MPU9250.AK8963_BIT_14, 1)

    def loop(self):
        while not rospy.is_shutdown():
            hello_str = "hello world %s" % rospy.get_time()
            rospy.loginfo(hello_str)
            self.pubPitch.publish(hello_str)
            self.rate.sleep()
            if self.mpu.checkDataReady():
                self.acc = self.mpu.readAccel()
                self.gyro = self.mpu.readGyro()
                self.mag = self.mpu.readMagnet()
                self.temp = self.mpu.readTemperature()

                print(f"acceleration is  {self.acc} gyro output is {self.gyro} mag is {self.mag} temp is {self.temp}")


if __name__ == '__main__':
    imu = IMU('testIMU')
    try:
        imu.loop()
    except rospy.ROSInterruptException:
       pass


