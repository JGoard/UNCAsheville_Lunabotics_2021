#!/usr/bin/env python

import rospy
from ds4_driver.msg import Status
from std_msgs.msg import Float32
import math

class wheel_drive(object):
    def __init__(self, left_publisher, right_publisher):
        self.left_publisher_ = left_publisher
        self.right_publisher_ = right_publisher
        self.max_vel = 1 #units: m/s

    def callback(self, msg):
        left_goal = Float32()
        right_goal = Float32()
        axis_l2 = getattr(msg, 'axis_l2')
        axis_r2 = getattr(msg, 'axis_r2')
        button_l1 = getattr(msg, 'button_l1')
        button_r1 = getattr(msg, 'button_r1')
        if button_l1:
            left_goal = -axis_l2*self.max_vel
        else:
            left_goal = axis_l2*self.max_vel
        if button_r1:
            right_goal = -axis_r2*self.max_vel
        else:
            right_goal = axis_r2*self.max_vel

        self.right_publisher_.publish(right_goal)
        self.left_publisher_.publish(left_goal)


def main():
    rospy.init_node('dualshock_teleop')
    left_publisher  = rospy.Publisher("left_drive_goal", Float32, queue_size=10)
    right_publisher = rospy.Publisher("right_drive_goal", Float32, queue_size=10)

    handle = wheel_drive(left_publisher = left_publisher, right_publisher = right_publisher)

    rospy.Subscriber('status', Status, handle.callback, queue_size=10)
    rospy.spin()


if __name__ == '__main__':
    main()
