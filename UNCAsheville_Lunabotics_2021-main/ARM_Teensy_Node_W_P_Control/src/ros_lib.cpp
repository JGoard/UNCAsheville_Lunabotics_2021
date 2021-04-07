#include <Arduino.h>
#include <ros.h>
#include "macros.h"
#include "functions.h"
#include <arm_handler/arm_msg.h>
#include <std_srvs/Empty.h>

extern ros::NodeHandle  nh;
extern ros::Publisher feedback;
extern ros::Subscriber<arm_handler::arm_msg> goal;
extern ros::ServiceServer<std_srvs::Empty::Request, std_srvs::Empty::Response> PID;
extern ros::ServiceServer<std_srvs::Empty::Request, std_srvs::Empty::Response> zero_pose;
extern arm_handler::arm_msg arm_pose;
extern arm_handler::arm_msg arm_goal;

extern int transStatus;

extern volatile uint16_t targetPose[ARM_DOF];

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: ros_init
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ros_init(void){

	nh.getHardware()->setBaud(ROS_BAUD);
	nh.initNode();
	nh.advertise(feedback);
	nh.subscribe(goal);
	nh.advertiseService(zero_pose); 
	while (!nh.connected()) nh.spinOnce();

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: ros_update
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ros_update(void){ 

	if (PUBLISH){
         // nh.logwarn("CONCAT");
          feedback.publish(&arm_pose);
		  nh.spinOnce();
          delay(10);

		  arm_pose.joint = 20;
		  arm_pose.data = analogRead(A13);

		  feedback.publish(&arm_pose);
		  nh.spinOnce();
          delay(10);
        }

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: goal_callback
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void goal_callback( const arm_handler::arm_msg &joint_goal){
	switch(joint_goal.joint){
		case WRIST_CHAR:{
			targetPose[WRIST] = joint_goal.data;
			break;
		}
		case ELBOW_CHAR:{
			targetPose[ELBOW] = joint_goal.data;
			break;
		}
		case SHOULDER_CHAR:{
			targetPose[SHOULDER] = joint_goal.data;
			break;
		}
		case HIP_CHAR:{
			targetPose[HIP] = joint_goal.data;
			break;
		}
		default:{
			nh.logfatal("invalid joint ID");
			break;
		}
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: zero_encoders
// Josh: 
// use this function to reset the zero position of the encoders
// We will need this functionality when we start moving the actual arm
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void zero_encoders(const std_srvs::Empty::Request &req, std_srvs::Empty::Response &res){
	nh.loginfo("Reset Encoders");
}

