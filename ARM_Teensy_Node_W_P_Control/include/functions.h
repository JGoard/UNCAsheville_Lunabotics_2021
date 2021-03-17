//Joshua Goard's RS-485 Work
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <arm_handler/arm_msg.h>
#include <std_srvs/Empty.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// rs485 functions
void rs485_init(void);
void pollEncoder(void);
void RS485Receive_EN(void);
void RS485Transmit_EN(void);
void RS485Transmit_Addr(void);
void RS485Receive_Pos(void);
void RS485ReceiveParse(void);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ROS functions
void ros_init(void);
void ros_update(void);
void goal_callback(const arm_handler::arm_msg &goal);
void update_PID(const std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);
void zero_encoders(const std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PID control functions
void PI_control(int);
void accumError(void);
float arraySum (uint16_t);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void positionZero(void);

#endif /* FUNCTIONS_H_ */
