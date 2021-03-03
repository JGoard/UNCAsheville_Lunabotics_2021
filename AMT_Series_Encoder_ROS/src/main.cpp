#include <Arduino.h>
//#include <SoftwareSerial.h>
#include <ros.h>
#include <ArduinoRS485.h>
#include <std_msgs/UInt16.h>
#include "macros.h"
#include "functions.h"


std_msgs::UInt16 wristElbow;
ros::NodeHandle  nh;
ros::Publisher pub("teensy_feedback", &wristElbow);


/* uint16_t byteIn;
uint16_t byteJetson;
uint8_t rxByte;
//uint16_t lowByte;
uint16_t data;
uint16_t lowByte;
uint16_t highByte;
uint16_t resolutionShift; */
//unsigned int wristElbow;
int transStatus;
bool published = true;
volatile extern bool encoderFlag;
unsigned long int currentMillis;

IntervalTimer encoderTimer;


void setup()   /****** SETUP: RUNS ONCE ******/
{

  rs485_init(); // RS485 pin config and serial init
  ros_init();   // setup ROS node handle, topic interfaces and parameters
  
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
 
  
   
}

