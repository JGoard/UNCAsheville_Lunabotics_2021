#include <Arduino.h>
#include <ros.h>
#include <arm_handler/arm_msg.h>
#include "macros.h"
#include "functions.h"


arm_handler::arm_msg arm_pose;
arm_handler::arm_msg arm_goal;

ros::NodeHandle  nh;
ros::Publisher feedback("arm_pose", &arm_pose);
ros::Subscriber<arm_handler::arm_msg> goal("arm_goal", &goal_callback);
ros::ServiceServer<std_srvs::Empty::Request, std_srvs::Empty::Response> zero_pose("zero_pose", &zero_encoders);

int transStatus = INIT;
bool published = true;
volatile extern bool encoderFlag;
IntervalTimer encoderTimer;
extern uint16_t encoderPositions[ARM_DOF];
volatile uint16_t targetPose [ARM_DOF] = {INIT_POSE};
volatile bool armSafe = true;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  ros_init();   // setup ROS node handle, topic interfaces and parameters
  rs485_init(); // RS485 pin config and serial init
  init_pin();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  digitalWrite(Pin13LED, HIGH);       //On when not transmitting

  monitorarmCurrent(); //Monitors arm current and will prevent future arm movement if over current drawn is sensed

  RS485Transmit_Addr(); // Includes Transmitting Code.
  RS485Receive_Pos(); //Receiving code for absolute encoders

 if(armSafe){ //Allows PI_Control of arm to function only if over current fault isn't set in monitorarmCurrent();

    for(int joint = WRIST; joint<=HIP; joint++) PI_control(joint);

 }

 else{                //If arm isn't safe, fails when current is overdrawn in any of the motors in monitorarmCurrent
                      //No way to reset this unless teensy is completely hard reset
                      //All PWM is turned off
  armcurrentProtection(); 

 }

  ros_update();
  nh.spinOnce();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void init_pin(void){
  pinMode(WRIST_PWM,OUTPUT);
  pinMode(WRIST_DIR,OUTPUT);
  pinMode(ELBOW_PWM,OUTPUT);
  pinMode(ELBOW_DIR,OUTPUT);
  pinMode(SHOULDER_PWM,OUTPUT);
  pinMode(SHOULDER_DIR,OUTPUT);
  pinMode(HIP_PWM,OUTPUT);
  pinMode(HIP_DIR,OUTPUT);
  pinMode(A13,INPUT); // Current sense pin, probably won't work due to PWM being wacky
  
}