#!/usr/bin/env python3
import rospy
from std_msgs.msg import String, Bool


class talker:
    def __init__(self):
        rospy.init_node('Starter', anonymous=True)
        self.pub = rospy.Publisher('/HJC/State_machine/Input', String, queue_size=1)
        rospy.Subscriber("/HJC/State_machine/Output", Bool, self.callback, queue_size=1)
        self.rate = rospy.Rate(10)  # 10hz
        self.end = False
        while not self.end:
            hello_str = "f"
            rospy.loginfo(hello_str)
            self.pub.publish(hello_str)
            self.rate.sleep()

    def callback(self, data: Bool):
        if data.data:
            self.end = True


if __name__ == "__main__":
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
