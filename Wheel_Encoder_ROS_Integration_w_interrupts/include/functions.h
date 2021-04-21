#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <std_msgs/Float32.h>

void setup(void);
void init_encoderCounter(void);

void frontleftEncoderCount(void);
void midleftEncoderCount(void);
void backleftEncoderCount(void);

void frontrightEncoderCount(void);
void midrightEncoderCount(void);
void backrightEncoderCount(void);

void calcVelocity(void);

void ros_init(void);

void leftdrive_callback(const std_msgs::Float32 &left_drive_goal);
void rightdrive_callback(const std_msgs::Float32 &right_drive_goal);








#endif