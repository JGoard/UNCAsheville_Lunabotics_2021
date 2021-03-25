#include <Arduino.h>
#include <ros.h>
#include "macros.h"
#include "functions.h"
#include <std_srvs/Empty.h>

extern ros::NodeHandle  nh;
extern ros::Publisher feedback;
//extern ros::Subscriber<std_msgs::> goal;
//extern u_int16_t::arm_msg arm_pose;
//extern u_int16_t::arm_msg arm_goal;

extern int transStatus;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: ros_init
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ros_init(void){

	nh.getHardware()->setBaud(ROS_BAUD);
	nh.initNode();
	nh.advertise(feedback);
	//nh.subscribe(goal);
	while (!nh.connected()) nh.spinOnce();

}
