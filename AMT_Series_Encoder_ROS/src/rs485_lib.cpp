#include <Arduino.h>
//#include <SoftwareSerial.h>
#include<ArduinoRS485.h>
#include<ros.h>
#include <std_msgs/UInt16.h>
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

extern std_msgs::UInt16 wristElbow;
extern ros::Publisher pub;


int byteOut[4]={WRIST, ELBOW, SHOULDER, HIP};


extern boolean isr_flag;
extern volatile int transStatus;

int encoderNodeCounter = INIT; //test


//////////////////////////////////////
/////////////////////////////////////


void rs485_init(void){
  //Serial.begin(9600); //NEED TO TURN OFF IF USING ROS
  encoderTimer.begin(pollEncoder,ENCODER_TIME_POLL);
 // while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
 //}
  //Serial.println("Serial ready for transmitting");
   
  pinMode(Pin13LED, OUTPUT);   
  pinMode(Re, OUTPUT);
  pinMode(De, OUTPUT);   
 
  //digitalWrite(RxTx, Receive);   //Initialize transciever to receive data
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
  if ((encoderFlag)&&(transStatus==INIT))
  {
    //Serial.println("Sent");           //Serial indicator
    nh.loginfo("RS485_TX");
    //byteOut = Serial.read;          //Locally store the transmitted string
    //Serial.println(byteOut[counter]);
    RS485Transmit_EN();
    Serial1.write(byteOut[encoderNodeCounter]);      // Send byte to encoder
    encoderNodeCounter++; //Increment node address array
    if (ENCODERS_CYCLED)
      encoderNodeCounter = INIT;

    digitalWrite(Pin13LED, LOW);      // Off momentarily
    delay(10);
    RS485Receive_EN();
    delay(50);
    

    encoderFlag = false;
  }
}

/////////////////////////////////////////////
/////////////////////////////////////////////

void RS485Receive_Pos(void){

  if (Serial1.available()&&(transStatus!=TRANS_END))       //Look for data from encoder
   {
     
    //Serial.println("Received");
    nh.loginfo("RS485_RX");
    digitalWrite(Pin13LED, LOW);        // Off momentarily
    byteIn = Serial1.read();     // Read received byte
    //Serial.println(byteIn);
    delay(10);

    switch (transStatus) //Parses through receiving bytes
    {
    case RXBACK:
      rxByte = byteIn;
     // Serial.println(rxByte, BIN); //What we sent
      break;

    case LOWBYTE:
      lowByte = byteIn; // The Low end of the countsT
       //Serial.println("LowByte");
       //Serial.println(lowByte,BIN);
       //nh.logwarn("did it");
    
    
      //Serial.println(lowByte, BIN);

      break;

    case HIGHBYTE:
      highByte = byteIn; 
       data = word(highByte, lowByte);
      data = data & HIGHBYTE_MASK; //Gets rid of top 2 checksum bits
      wristElbow.data = data >> SHIFT_RES;
     
      break;


    default:
      break;
    }
    transStatus++;
      if (PUBLISH){
      nh.logwarn("CONCAT");
      pub.publish(&wristElbow);
      nh.spinOnce();
      delay(10);
      }
  }

else transStatus = INIT;

}