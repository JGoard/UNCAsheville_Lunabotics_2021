#include <Arduino.h>
//#include <SoftwareSerial.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <arm_subscriber/arm_msg.h>
#include "macros.h"
#include "functions.h"
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>


arm_subscriber::arm_msg wristElbow;
ros::NodeHandle  nh;
ros::Publisher pub("arm_pose", &wristElbow);

int transStatus;
bool published = true;
volatile extern bool encoderFlag;
unsigned long int currentMillis;

IntervalTimer encoderTimer;

boolean tuning = true;
byte ATuneModeRemember=2;


double aTuneStep=10, aTuneNoise=1, aTuneStartValue=30;
unsigned int aTuneLookBack=20;

double setpoint = 1000;

double target_pwm, kp =1 , ki =1, kd =1;

extern double encoderPositions[4];

//Specify the links and initial tuning parameters
//double Kp=2, Ki=5, Kd=1;

void setup()   /****** SETUP: RUNS ONCE ******/
{


  ros_init();   // setup ROS node handle, topic interfaces and parameters
  rs485_init(); // RS485 pin config and serial init

}
char buffer [33];

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


 if (PUBLISH){
          //nh.logwarn("CONCAT");
          pub.publish(&wristElbow);
          nh.spinOnce();
          delay(10);
        }
}

