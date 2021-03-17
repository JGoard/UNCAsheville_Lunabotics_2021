#include <Arduino.h>
#include<ros.h>
#include <arm_handler/arm_msg.h>
#include "macros.h"
#include "functions.h"

extern ros::NodeHandle  nh;
extern arm_handler::arm_msg arm_pose;

char byteOut[ARM_DOF]={WRIST, ELBOW, SHOULDER, HIP};
uint16_t encoderPositions[ARM_DOF];


uint16_t byteIn;
uint16_t byteJetson;
uint8_t rxByte;
uint16_t data;
uint16_t lowByte;
uint16_t highByte;
uint16_t resolutionShift;

extern IntervalTimer encoderTimer;
volatile boolean encoderFlag;

//extern boolean isr_flag;
extern volatile int transStatus;

int encoderNodeCounter = INIT; //test


//////////////////////////////////////
/////////////////////////////////////


void rs485_init(void){

  encoderTimer.begin(pollEncoder,ENCODER_TIME_POLL); //Move this so that it will 
                                                     //be triggered by a subscriber talking to theTeensy
  pinMode(Pin13LED, OUTPUT);   
  pinMode(Re, OUTPUT);
  pinMode(De, OUTPUT);   
 
  RS485Receive_EN(); 

  Serial1.begin(115200, SERIAL_8N1);        // set the data rate

}

/////////////////////////////////////
/////////////////////////////////////


void RS485Transmit_EN() //Enables rs485 Transmission
{
  digitalWrite(Re, LOW);   
  digitalWrite(De, HIGH);   
}


/////////////////////////////////////////////
/////////////////////////////////////////////


void RS485Receive_EN()  //Enables rs485 Reception
{
  digitalWrite(Re, HIGH);   
  digitalWrite(De, LOW); 
}


/////////////////////////////////////////////
/////////////////////////////////////////////


void pollEncoder(void)
{
  encoderFlag = true;
}

/////////////////////////////////////////////
/////////////////////////////////////////////


void RS485Transmit_Addr(void){
  
   if (ENCODERS_CYCLED){
      nh.logwarn("CYCLED");
      encoderNodeCounter = INIT;
    }
    
  if ((encoderFlag)&&(transStatus==INIT))
  {
    nh.loginfo("RS485_TX");
    
    RS485Transmit_EN();
    Serial1.write(byteOut[encoderNodeCounter]);      // Send byte to encoder
    (byteOut[encoderNodeCounter]);
    arm_pose.joint = byteOut[encoderNodeCounter];
    encoderNodeCounter++; //Increment node address array

   

    digitalWrite(Pin13LED, LOW);      // Off momentarily
    delay(10);
    RS485Receive_EN();
    delay(10);
    

    encoderFlag = false;
  }
}

/////////////////////////////////////////////
/////////////////////////////////////////////

void RS485Receive_Pos(void){

  if (Serial1.available()&&(transStatus!=TRANS_END))       //Look for data from encoder
   {
    nh.loginfo("RS485_RX");
    digitalWrite(Pin13LED, LOW);        // Off momentarily
    byteIn = Serial1.read();     // Read received byte
    //delay(10);

    switch (transStatus) //Parses through receiving bytes
    {
        case RXBACK:
          rxByte = byteIn;
          break;

        case LOWBYTE:
          lowByte = byteIn; // The Low end of the countsT
          break;

        case HIGHBYTE:
          highByte = byteIn; 
          data = word(highByte, lowByte);
          data = data & HIGHBYTE_MASK; //Gets rid of top 2 checksum bits
          arm_pose.data = data >> SHIFT_RES;
          encoderPositions[encoderNodeCounter] = arm_pose.data; //records data from W,E,S,H and assigns to 
          
          break;                                                  //each variable

          default:
          break;

    }
       transStatus++;

       
        /* if (PUBLISH){
          nh.logwarn("CONCAT");
          pub.publish(&arm_pose);
          nh.spinOnce();
          delay(10);
        } */
  }

else transStatus = INIT;

}