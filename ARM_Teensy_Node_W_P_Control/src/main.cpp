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

  RS485Transmit_Addr(); // Includes Transmitting Code. Only allows for two
                        // two node addresses currently.  Would be nice if 
                        // we could speed up publishing speed.  logwarns start
                        // to collide once we get to around 1/10 of a sec
                        // for encoder polling (ENCODER_TIME_POLL)

    
  
  RS485Receive_Pos();

  for(int joint = WRIST; joint<=HIP; joint++) PI_control(joint);

  ros_update();
  nh.spinOnce();
}



void init_pin(void){
  pinMode(WRIST_PWM,OUTPUT);
  pinMode(WRIST_DIR,OUTPUT);
  pinMode(ELBOW_PWM,OUTPUT);
  pinMode(ELBOW_DIR,OUTPUT);
  pinMode(SHOULDER_PWM,OUTPUT);
  pinMode(SHOULDER_DIR,OUTPUT);
  pinMode(HIP_PWM,OUTPUT);
  pinMode(HIP_DIR,OUTPUT);
  pinMode(A13,INPUT);
}