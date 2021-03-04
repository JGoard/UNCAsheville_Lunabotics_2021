#include <Arduino.h>
//#include <SoftwareSerial.h>
#include<ros.h>
#include <std_msgs/UInt16.h>
#include <arm_subscriber/arm_msg.h>
#include "macros.h"
#include "functions.h"
extern IntervalTimer encoderTimer;
volatile boolean encoderFlag;
//volatile extern int byteOut;
extern ros::NodeHandle  nh;



uint16_t byteIn;
uint16_t byteJetson;
uint8_t rxByte;
//uint16_t lowByte;
uint16_t data;
uint16_t lowByte;
uint16_t highByte;
uint16_t resolutionShift;

extern arm_subscriber::arm_msg wristElbow;
extern ros::Publisher pub;
 char byteOut[4]={WRIST, ELBOW, SHOULDER, HIP};


extern boolean isr_flag;
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
  char swamp;
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
    wristElbow.joint = byteOut[encoderNodeCounter];
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
         // wristElbow.data = data >> SHIFT_RES;
          wristElbow.data = data;
          break;

          default:
          break;

    }
       transStatus++;

       
        /* if (PUBLISH){
          nh.logwarn("CONCAT");
          pub.publish(&wristElbow);
          nh.spinOnce();
          delay(10);
        } */
  }

else transStatus = INIT;

}