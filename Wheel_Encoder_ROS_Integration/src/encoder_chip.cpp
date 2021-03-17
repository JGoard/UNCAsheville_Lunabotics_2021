#include <Arduino.h>
#include "macros.h"
#include "functions.h"

extern volatile int currentEncoderVal;

void init_encoderCounter(void){

    digitalWrite(0,HIGH);
    digitalWrite(1,LOW);
    analogWrite(2,25); //Not sure why these values are here or 
    analogWrite(3,50); //their significance
    digitalWrite(CCKEN,LOW);
    digitalWrite(CCLR,HIGH);

}

void encoderCount(void){

  if(digitalRead(BITF_0)){
    val += ONES;
  }
  if(digitalRead(BITF_1)){
    val += TWOS;
  }
  if(digitalRead(BITF_2)){
    val += THREES;
  }
  if(digitalRead(BITF_3)){
    val += FOURS;
  }
  if(digitalRead(BITF_4)){
    val += FIVES;
  }
  if(digitalRead(BITF_5)){
    val += SIXTHS;
  }
  if(digitalRead(BITF_6)){
    val += SEVENTHS;
  }
  if(digitalRead(BITF_7)){
    val += EIGHTHS;
  }




}