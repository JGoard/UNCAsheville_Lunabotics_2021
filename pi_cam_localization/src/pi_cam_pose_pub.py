#!/usr/bin/env python

import rospy

from geometry_msgs.msg import PoseWithCovarianceStamped
from ar_track_alvar_msgs.msg import AlvarMarkers
from ar_track_alvar_msgs.msg import AlvarMarker

class pose_converter():

    def __init__(self):
        self.sub = rospy.Subscriber('ar_pose_marker',AlvarMarkers,self.sub_cb)
        self.pub = rospy.Publisher('ar_tag_pose', PoseWithCovarianceStamped, queue_size=10)
        self.ar_id = []

    def sub_cb(self,msg):
        marker_list = msg.markers
        tmp = AlvarMarkers()
        for alvar_marker in marker_list:
            pose_msg = PoseWithCovarianceStamped()
            pose_msg.header.stamp = rospy.Time.now()
            if alvar_marker.id in self.ar_id: 
                pose_msg.pose.pose = alvar_marker.pose.pose
                pose_msg.header.frame_id = str(alvar_marker.id)
                self.pub.publish(pose_msg)


if __name__ == '__main__':
    try:
        if not rospy.has_param('~tag'):
            rospy.set_param('~tag', [61,62])

        rospy.init_node('ar_tag_publisher')
        master = pose_converter()
        master.ar_id = rospy.get_param('~tag')
        rospy.loginfo('Starting AR Pose Publishing Node')
        rospy.loginfo('Using AR tag ID list: '+str(master.ar_id))
        while not rospy.is_shutdown():
            rospy.spin()
    except rospy.ROSInterruptException:
        pass


