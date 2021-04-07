#!/usr/bin/env python3

import board
import busio
import rospy
import adafruit_lsm6ds

from sensor_msgs.msg import Imu


def main():

    rospy.init_node('accelerometer', anonymous=False)
    pub = rospy.Publisher("imu", Imu, queue_size=10)

    rospy.loginfo('MMA8451 3DOF Accelerometer Publishing to IMU')

    i2c = busio.I2C(board.SCL, board.SDA)
    sensor = adafruit_lsm6ds.LSM6DSOX(i2c)
    
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
        imu_msg.linear_acceleration.x = x
        imu_msg.linear_acceleration.y = y
        imu_msg.linear_acceleration.z = z
        pub.publish(imu_msg)
        rospy.sleep(1)

    rospy.logwarn('MMA8451 Accelerometer Offline')

    
if __name__ == '__main__':
    main()