#include <Arduino.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include "macros.h"
#include "functions.h"
#include <arm_subscriber/arm_msg.h>

boolean isr_flag = false;
extern ros::NodeHandle  nh;
extern ros::Publisher pub;


void ros_init(void){

	nh.getHardware()->setBaud(57600);
	nh.initNode();
	nh.advertise(pub);
	
	while (!nh.connected()) nh.spinOnce();
	//if (isr_flag) nh.loginfo("isr enabled");
	//else nh.logerror("isr disabled");

}


