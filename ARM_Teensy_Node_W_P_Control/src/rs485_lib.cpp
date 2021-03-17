#include <Arduino.h>
#include<ros.h>
#include <arm_handler/arm_msg.h>
#include "macros.h"
#include "functions.h"
//volatile extern int byteOut;

extern ros::NodeHandle  nh;
extern volatile arm_handler::arm_msg arm_pose;

char byteOut[ARM_DOF]={WRIST_CHAR, ELBOW_CHAR, SHOULDER_CHAR, HIP_CHAR};
uint16_t encoderPositions[ARM_DOF];


uint16_t byteIn;
uint8_t rxByte;
uint16_t data;
uint16_t nodelowByte;
uint16_t nodehighByte;
uint16_t resolutionShift;

extern IntervalTimer encoderTimer;
volatile boolean encoderFlag;

extern boolean isr_flag;
extern volatile int transStatus;

int encoderNodeCounter = INIT; //test


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: rs485_init
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void rs485_init(void){

  encoderTimer.begin(pollEncoder,ENCODER_TIME_POLL); //Move this so that it will 
                                                     //be triggered by a subscriber talking to theTeensy
  pinMode(Pin13LED, OUTPUT);   
  pinMode(Re, OUTPUT);
  pinMode(De, OUTPUT);   
 
  RS485Receive_EN(); 

  Serial1.begin(RS485_BAUD, SERIAL_8N1);        // set the data rate

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: RS485Transmit_EN
// - Enables rs485 Transmission
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void RS485Transmit_EN(void){
  digitalWrite(Re, LOW);   
  digitalWrite(De, HIGH);   
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: RS485Receive_EN
// - Enables rs485 Reception
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void RS485Receive_EN(void){
  digitalWrite(Re, HIGH);   
  digitalWrite(De, LOW); 
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: pollEncoder
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pollEncoder(void){
  encoderFlag = true;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: RS485Transmit_Addr
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void RS485Transmit_Addr(void){

   if (ENCODERS_CYCLED){
      nh.logwarn("CYCLED");
      encoderNodeCounter = INIT;
    }
    
  if ((encoderFlag)&&(transStatus==INIT)){
    nh.loginfo("RS485_TX");

    RS485Transmit_EN();
    //delay(10);
    Serial1.write(byteOut[encoderNodeCounter]);      // Send byte to encoder
    //(byteOut[encoderNodeCounter]);
    arm_pose.joint = byteOut[encoderNodeCounter++];

   

    digitalWrite(Pin13LED, LOW);      // Off momentarily
    delay(10);
    RS485Receive_EN();
    delay(10);
    

    encoderFlag = false;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: RS485Receive_Pos
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void RS485Receive_Pos(void){

  //sif (!Serial1.available()) nh.logerror("Not available");

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
          nodelowByte = byteIn; // The Low end of the countsT
          break;

        case HIGHBYTE:
          nodehighByte = byteIn; 
          data = word(nodehighByte, nodelowByte);
          data = data & HIGHBYTE_MASK; //Gets rid of top 2 checksum bits
          arm_pose.data = data >> SHIFT_RES;
          encoderPositions[encoderNodeCounter-1] = arm_pose.data; //records data from W,E,S,H and assigns to 
          //encoderNodeCounter++; //Increment node address array
          nh.logwarn("CONCAT");
          

          break;                                                  //each variable

        default:
          nh.logwarn("SHIT");
          break;

    }
       transStatus++;

  }

else transStatus = INIT;

}