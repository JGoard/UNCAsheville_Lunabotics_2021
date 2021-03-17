#include <Arduino.h>
#include "macros.h"
#include "functions.h"


void setup() {
  // put your setup code here, to run once:
init_encoderCounter(); //Initialize encoder chip and pins
Serial.begin(9600);
}

void loop() {
  int val=INIT;
  digitalWrite(CCLR,LOW); //Not sure why these are here
  delay(20);
  digitalWrite(CCLR,HIGH);
  
  delay(200);

  if(digitalRead(BIT0)){
    val += ONES;
  }
  if(digitalRead(BIT1)){
    val += TWOS;
  }
  if(digitalRead(BIT2)){
    val += THREES;
  }
  if(digitalRead(BIT3)){
    val += FOURS;
  }
  if(digitalRead(BIT4)){
    val += FIVES;
  }
  if(digitalRead(BIT5)){
    val += SIXTHS;
  }
  if(digitalRead(BIT6)){
    val += SEVENTHS;
  }
  if(digitalRead(BIT7)){
    val += EIGHTHS;
  }
  
  Serial.println(val);

  
  
  // put your main code here, to run repeatedly:

}
