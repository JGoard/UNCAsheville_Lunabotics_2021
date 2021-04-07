#!/usr/bin/env python3

import board
import busio
import rospy
from adafruit_lsm6ds.lsm6dsox import LSM6DSOX
from sensor_msgs.msg import Imu


def main():

    rospy.init_node('accelerometer', anonymous=False)
    pub = rospy.Publisher("imu", Imu, queue_size=10)

    
    print(board.SCL, board.SDA)
    i2c = busio.I2C(board.SCL, board.SDA)
    sensor = LSM6DSOX(i2c)

    rospy.loginfo('ISM330DHCX 6DOF Accelerometer Publishing to IMU')

    imu_msg = Imu()
    
    imu_msg.linear_acceleration_covariance = [
        0, 0, 0, 
        0, 0, 0, 
        0, 0, 0 
    ]
    imu_msg.angular_velocity_covariance = [
        0, 0, 0, 
        0, 0, 0, 
        0, 0, 0 
    ]
    while not rospy.is_shutdown():
        x, y, z = sensor.acceleration
        u,v,w = sensor.gyro
        imu_msg.angular_velocity.x = u
        imu_msg.angular_velocity.y = v
        imu_msg.angular_velocity.z = w
        imu_msg.linear_acceleration.x = x
        imu_msg.linear_acceleration.y = y
        imu_msg.linear_acceleration.z = z
        pub.publish(imu_msg)
        rospy.sleep(1)

    rospy.loginfo('ISM330DHCX Accelerometer Offline')
    
if __name__ == '__main__':
    main()