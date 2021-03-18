#include <Arduino.h>
#include "macros.h"
#include "functions.h"

extern volatile int currentEncoderVal;

void init_encoderCounter(void){
  
    pinMode(BITF_0,INPUT);
    pinMode(BITF_1,INPUT);
    pinMode(BITF_2,INPUT);
    pinMode(BITF_3,INPUT);
    pinMode(BITF_4,INPUT);
    pinMode(BITF_5,INPUT);
    pinMode(BITF_6,INPUT);
    pinMode(BITF_7,INPUT);

    pinMode(MRC_F ,OUTPUT);
    pinMode(CPR_F,OUTPUT);

    digitalWrite(MRC_F,HIGH);
    digitalWrite(CPR_F,LOW);

    pinMode(F_MOTOR_PWM ,OUTPUT);
    pinMode(F_MOTOR_DIR,OUTPUT);
    digitalWrite(F_MOTOR_DIR,HIGH);
    digitalWrite(F_MOTOR_PWM,100);

}

void encoderCount(void){

  if(digitalRead(BITF_0)){
    currentEncoderVal += ONES;
  }
  if(digitalRead(BITF_1)){
    currentEncoderVal += TWOS;
  }
  if(digitalRead(BITF_2)){
    currentEncoderVal += THREES;
  }
  if(digitalRead(BITF_3)){
    currentEncoderVal += FOURS;
  }
  if(digitalRead(BITF_4)){
    currentEncoderVal += FIVES;
  }
  if(digitalRead(BITF_5)){
    currentEncoderVal += SIXTHS;
  }
  if(digitalRead(BITF_6)){
    currentEncoderVal += SEVENTHS;
  }
  if(digitalRead(BITF_7)){
    currentEncoderVal += EIGHTHS;
  }



 /*  switch (ENCODER_COUNT)  //Would like to see some parrallel port processing used besides the digitalReads like up above
  {                          //It's a nasty way to bottle neck up the system
  case :

  case   
  
  default:
    break;
  } */


}