#include <Arduino.h>
#include "macros.h"
#include "functions.h"

volatile int frontCount = INIT;
volatile int midCount = INIT;
volatile int backCount = INIT;


//////////////
//Encoder Pin initialization
//Will be setting pins for the front, mid, and back wheels
//to hardware interrupt pins acting on a RISING change
//enabling and disenabling interrupt 
//////////////
void init_encoderCounter(void){
  
   pinMode(F_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(M_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(B_HALL_CHANNEL, INPUT_PULLUP);
  
   attachInterrupt(F_HALL_CHANNEL, frontEncoderCount, RISING); //attaching interrupt functions to 
   attachInterrupt(M_HALL_CHANNEL, midEncoderCount, RISING);   //these pins
   attachInterrupt(B_HALL_CHANNEL, backEncoderCount, RISING);


    pinMode(F_MOTOR_PWM, OUTPUT);
    pinMode(F_MOTOR_DIR,OUTPUT);

    pinMode(M_MOTOR_PWM, OUTPUT);
    pinMode(M_MOTOR_DIR, OUTPUT)

    pinMode(B_MOTOR_PWM, OUTPUT);
    pinMode(B_MOTOR_DIR, OUTPUT)

    digitalWrite(F_MOTOR_DIR,HIGH);
    digitalWrite(F_MOTOR_PWM,100);

}

//////////////
//ISR for front wheel encoder 
//////////////

void frontEncoderCount(void){

  

frontCount++;



}

//////////////
//ISR for mid wheel encoder
//////////////

void midEncoderCount(void){

  

midCount++;



}

//////////////
//ISR for back wheel encoder
//////////////

void backEncoderCount(void){

  

backCount++;



}