#include <Arduino.h>
#include "macros.h"
#include "functions.h"

extern volatile int currentEncoderVal;

void init_encoderCounter(void){

    digitalWrite(0,HIGH);
    digitalWrite(1,LOW);
    analogWrite(2,25); //Not sure why these values are here or 
    analogWrite(3,50); //their significance
    digitalWrite(CCKEN_F,LOW);
    digitalWrite(CCLR_F,HIGH);

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