#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>

volatile int currentEncoderVal = INIT;
// Create an IntervalTimer object 
IntervalTimer myTimer;


void pub_vel(void) {

    digitalWrite(CPR_F,HIGH);
    encoderCount();
    digitalWrite(MRC_F,LOW);
    delay(2);
    Serial.println(currentEncoderVal);
    digitalWrite(MRC_F,HIGH);
    digitalWrite(CPR_F,LOW);
    currentEncoderVal = INIT;

}


void setup() {

init_encoderCounter(); //Initialize encoder chip and pins
Serial.begin(9600);
myTimer.begin(pub_vel, 10000);
}

void loop() {
}