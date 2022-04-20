#!/usr/bin/env python
import time

import rospy
from std_msgs.msg import Float64


class Gradual:
    def __init__(self):
        self.current_velocity = 0
        self.pub = rospy.Publisher("/HJC/Vel_robot/Set_velocity", Float64, queue_size=10)
        self.subs = rospy.Subscriber("/HJC/Vel_robot/Current_velocity", Float64, self.callback, queue_size=10)
        self.rate = rospy.Rate(200)

    def callback(self, msg: Float64):
        self.current_velocity = msg.data
        # rospy.loginfo("Callback: {}".format(self.current_velocity))

    def go(self):
        while not rospy.is_shutdown():

            scale = 2
            for i in range(0, int(54/scale)):
                vel = -i * 3.6 * scale
                rospy.loginfo("Go Velocity: {}".format(vel))
                self.pub.publish(Float64(vel))
                #while not close(self.current_velocity, vel, 1):
                self.rate.sleep()
                time.sleep(1)
            '''
            for i in range(2, 6):
                vel = -i * 100
                rospy.loginfo("Go Velocity: {}".format(vel))
                self.pub.publish(Float64(vel))
                while not close(self.current_velocity, vel, 1):
                    pass
            '''



def close(num, n, perc):
    per1 = perc * 0.01
    m = 1
    if num < 0:
        m = -1
    up = n * (1 + m * per1)
    down = n * (1 - m * per1)
    # rospy.loginfo_throttle(.5, "{} > {} > {}?".format(up, num, down))
    if up > num > down:
        # rospy.logerr("YEAH!!")
        return True
    return False


if __name__ == "__main__":
    rospy.init_node("gradual")
    gradual = Gradual()
    gradual.go()
