#include <Arduino.h>
#include <ros.h>
#include "macros.h"
#include "functions.h"
#include <arm_handler/arm_msg.h>
#include <std_srvs/Empty.h>

extern ros::NodeHandle  nh;
extern ros::Publisher feedback;
extern ros::Subscriber<arm_handler::arm_msg> goal;
//extern ros::ServiceServer<std_srvs::Empty::Request, std_srvs::Empty::Response> PID;
//extern ros::ServiceServer<std_srvs::Empty::Request, std_srvs::Empty::Response> zero_pose;
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
	//nh.advertiseService(zero_pose); 
	while (!nh.connected()) nh.spinOnce();

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: ros_update
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ros_update(void){ 

		if(PUBLISH){
          //nh.logwarn("Update");
          feedback.publish(&arm_pose);
		  nh.spinOnce();
          delay(3);
		}
	/* 	  arm_pose.joint = 20;
		  arm_pose.data = analogRead(A13); */
        

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: goal_callback
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void goal_callback( const arm_handler::arm_msg &joint_goal){
	switch(joint_goal.joint){
		case WRIST_CHAR:{
			if(WRIST_LIMIT){
				targetPose[WRIST] = joint_goal.data;
			}
			else{

              if (WRIST_LOW_LIMIT_COMP && !WRIST_HIGH_LIMIT_COMP)   //If the target pose is higher than the lower limit, and is higher than the 
                  targetPose[WRIST] = WRIST_HIGH_LIMIT;              //Highest limit, it will assign the high limit 
               

              if (!WRIST_LOW_LIMIT_COMP && WRIST_HIGH_LIMIT_COMP)             //If the target pose is lower than the lower limit, and is lower than the high
                 targetPose[WRIST] = WRIST_LOW_LIMIT;                //limit, the wrist stays in the low position
			}
			break;
		}
		case ELBOW_CHAR:{
			if(ELBOW_LIMIT){
				targetPose[ELBOW] = joint_goal.data;
			}
			else{

              if (ELBOW_LOW_LIMIT_COMP && !ELBOW_HIGH_LIMIT_COMP)   //If the target pose is higher than the lower limit, and is higher than the 
                  targetPose[ELBOW] = ELBOW_HIGH_LIMIT;              //Highest limit, it will assign the high limit 
               

              if (!ELBOW_LOW_LIMIT_COMP && ELBOW_HIGH_LIMIT_COMP)             //If the target pose is lower than the lower limit, and is lower than the high
                 targetPose[ELBOW] = ELBOW_LOW_LIMIT;                //limit, the ELBOW stays in the low position
			}			break;
		}
		case SHOULDER_CHAR:{
			if(SHOULDER_LIMIT){
				targetPose[SHOULDER] = joint_goal.data;
			}
			else{

              if (SHOULDER_LOW_LIMIT_COMP && !SHOULDER_HIGH_LIMIT_COMP)   //If the target pose is higher than the lower limit, and is higher than the 
                  targetPose[SHOULDER] = SHOULDER_HIGH_LIMIT;              //Highest limit, it will assign the high limit 
               

              if (!SHOULDER_LOW_LIMIT_COMP && SHOULDER_HIGH_LIMIT_COMP)             //If the target pose is lower than the lower limit, and is lower than the high
                 targetPose[SHOULDER] = SHOULDER_LOW_LIMIT;                //limit, the wrist stays in the low position
			}			break;
		}
		case HIP_CHAR:{
			if(HIP_LIMIT){
				targetPose[HIP] = joint_goal.data;
			}
			else{

              if (HIP_LOW_LIMIT_COMP && !HIP_HIGH_LIMIT_COMP)   //If the target pose is higher than the lower limit, and is higher than the 
                  targetPose[HIP] = HIP_HIGH_LIMIT;              //Highest limit, it will assign the high limit 
               

              if (!HIP_LOW_LIMIT_COMP && HIP_HIGH_LIMIT_COMP)             //If the target pose is lower than the lower limit, and is lower than the high
                 targetPose[HIP] = HIP_LOW_LIMIT;                //limit, the HIP stays in the low position
			}				break;
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

