#include <Arduino.h>
#include <ros.h>
#include <arm_subscriber/arm_msg.h>
#include "macros.h"
#include "functions.h"

arm_subscriber::arm_msg wristElbow;
ros::NodeHandle  nh;
ros::Publisher pub("arm_pose", &wristElbow);

int transStatus;
bool published = true;
volatile extern bool encoderFlag;
unsigned long int currentMillis;

IntervalTimer encoderTimer;


double setpoint = 1000;

extern double encoderPositions[4];

//Specify the links and initial tuning parameters
//double Kp=2, Ki=5, Kd=1;

void setup()   /****** SETUP: RUNS ONCE ******/
{


  ros_init();   // setup ROS node handle, topic interfaces and parameters
  rs485_init(); // RS485 pin config and serial init

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


 if (PUBLISH){
          //nh.logwarn("CONCAT");
          pub.publish(&wristElbow);
          nh.spinOnce();
          delay(10);
        }
}

