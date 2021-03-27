#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>

volatile int frontCount = INIT;
volatile int midCount = INIT;
volatile int backCount = INIT;

bool printFront = false;
bool printMid = false;
bool printBack = false;
IntervalTimer velCalc;
float frontVelocity;



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
   attachInterrupt(B_HALL_CHANNEL, backEncoderCount, RISING);  //Currently, these wheels will spin 300 counts
                                                               //per revolution


    pinMode(F_MOTOR_PWM, OUTPUT);
    pinMode(F_MOTOR_DIR,OUTPUT);

    pinMode(M_MOTOR_PWM, OUTPUT);
   // pinMode(M_MOTOR_DIR, OUTPUT);

    pinMode(B_MOTOR_PWM, OUTPUT);
   // pinMode(B_MOTOR_DIR, OUTPUT);

    digitalWrite(F_MOTOR_DIR,HIGH);
    digitalWrite(F_MOTOR_PWM,100);
    velCalc.begin(calcVelocity, VELOCITY_CALC_TIMER); //Currently set at 100 Hz

}

//////////////
//ISR for front wheel encoder 
//////////////

void frontEncoderCount(void){

  

frontCount++;
printFront = true;



}

//////////////
//ISR for mid wheel encoder
//////////////

void midEncoderCount(void){

  

midCount++;
printMid = true;



}

//////////////
//ISR for back wheel encoder
//////////////

void backEncoderCount(void){

  

backCount++;
printBack = true;



}



/* 
Circumference is 2*Pi*r.  Angular velocity is just unit distance per second. 
So how many pulses per revolution, what is the circumference? 
Circumference divided by pulses per revolution = distance per pulse. Measure the time per pulse, 
distance per pulse divided by time per pulse = distance/time. */


void calcVelocity(){
    
    int frontDistance = frontCount * DIST_PER_PULSE; //Will calculate amount traveled, frontCount is rising edge based
    frontCount = INIT;
    frontVelocity = frontDistance * VELOCITY_TIME_DIVIDER;  //Since calcVelocity is running 100 times a second, multiplied by 1/100 sec





}