#include <Arduino.h>
#include <ros.h>
#include "macros.h"
#include "functions.h"
#include <arm_handler/arm_msg.h>

boolean isr_flag = false;
extern ros::NodeHandle  nh;
extern ros::Publisher feedback;
extern arm_handler::arm_msg arm_pose;

extern int transStatus;

void ros_init(void){

	nh.getHardware()->setBaud(57600);
	nh.initNode();
	nh.advertise(feedback);
	
	while (!nh.connected()) nh.spinOnce();
	//if (isr_flag) nh.loginfo("isr enabled");
	//else nh.logerror("isr disabled");

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: ros_update
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ros_update(void){ 

	if (transStatus == 3){
         // nh.logwarn("CONCAT");
          feedback.publish(&arm_pose);
		  nh.spinOnce();
          delay(10);
        }

}