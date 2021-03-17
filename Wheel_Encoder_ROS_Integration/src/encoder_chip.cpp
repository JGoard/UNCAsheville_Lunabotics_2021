#include <Arduino.h>
#include "macros.h"
#include "functions.h"

void init_encoderCounter(void){

    digitalWrite(0,HIGH);
    digitalWrite(1,LOW);
    analogWrite(2,25); //Not sure why these values are here or 
    analogWrite(3,50); //their significance
    digitalWrite(CCKEN,LOW);
    digitalWrite(CCLR,HIGH);

}