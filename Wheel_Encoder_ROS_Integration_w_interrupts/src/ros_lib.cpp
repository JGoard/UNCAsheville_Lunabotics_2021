#include <Arduino.h>
#include <ros.h>
#include "macros.h"
#include "functions.h"
#include <std_srvs/Empty.h>
#include<std_msgs/Float32.h>

extern ros::NodeHandle  nh;
extern ros::Publisher leftvelPub;
extern ros::Publisher rightvelPub;

std_msgs::Float32 right_vel;
std_msgs::Float32 left_vel;


ros::Subscriber<std_msgs::Float32> right_drive_goal("right_drive_goal", &rightdrive_callback);
ros::Subscriber<std_msgs::Float32> left_drive_goal("left_drive_goal", &leftdrive_callback);

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
	nh.advertise(leftvelPub);
	nh.advertise(rightvelPub);
	nh.subscribe(right_drive_goal);
	nh.subscribe(left_drive_goal);

	//nh.subscribe(goal);
	while (!nh.connected()) nh.spinOnce();

}

void leftdrive_callback(const std_msgs::Float32 &left_drive_goal){
	int	PWM_Value = int (left_drive_goal.data*180);



	if(left_drive_goal.data < 0){
		digitalWrite(LEFT_SIDE_DIR, HIGH);
		PWM_Value = abs(PWM_Value);
		analogWrite(FL_MOTOR_PWM, PWM_Value);
		analogWrite(ML_MOTOR_PWM, PWM_Value);
		analogWrite(BL_MOTOR_PWM, PWM_Value);
  
	}

	if(left_drive_goal.data > 0){
		digitalWrite(LEFT_SIDE_DIR, LOW);
		analogWrite(FL_MOTOR_PWM, PWM_Value);
		analogWrite(ML_MOTOR_PWM, PWM_Value);
		analogWrite(BL_MOTOR_PWM, PWM_Value);

	}

	if(left_drive_goal.data == 0){
		analogWrite(FL_MOTOR_PWM,0);
		analogWrite(ML_MOTOR_PWM, 0);
		analogWrite(BL_MOTOR_PWM, 0);

	}


}

void rightdrive_callback(const std_msgs::Float32 &right_drive_goal){
	
	int PWM_Value = int (right_drive_goal.data*180);
	
	if(right_drive_goal.data < 0){
		digitalWrite(RIGHT_SIDE_DIR, LOW);
		PWM_Value = abs(PWM_Value);
		analogWrite(FR_MOTOR_PWM, PWM_Value);
		analogWrite(MR_MOTOR_PWM, PWM_Value);
		analogWrite(BR_MOTOR_PWM, PWM_Value);
  
	}

	if(right_drive_goal.data > 0){
		digitalWrite(RIGHT_SIDE_DIR, HIGH);
		analogWrite(FR_MOTOR_PWM, PWM_Value);
		analogWrite(MR_MOTOR_PWM, PWM_Value);
		analogWrite(BR_MOTOR_PWM, PWM_Value);

	}

	if(right_drive_goal.data == 0){
		analogWrite(FR_MOTOR_PWM,0);
		analogWrite(MR_MOTOR_PWM, 0);
		analogWrite(BR_MOTOR_PWM, 0);

	}



}