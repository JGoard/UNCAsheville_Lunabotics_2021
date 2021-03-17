#include <Arduino.h>
#include "macros.h"
#include "functions.h"

volatile int currentEncoderVal =INIT;


void setup() {
  // put your setup code here, to run once:
init_encoderCounter(); //Initialize encoder chip and pins
Serial.begin(9600);
}

void loop() {
  digitalWrite(CCLR,LOW); //Not sure why these are here
  delay(20);
  digitalWrite(CCLR,HIGH);
  
  delay(10);

  encoderCount();
  
  Serial.println(val);

  
  
  // put your main code here, to run repeatedly:

}
