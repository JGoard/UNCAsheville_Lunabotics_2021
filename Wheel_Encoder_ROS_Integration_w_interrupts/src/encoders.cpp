#include <Arduino.h>
#include "macros.h"
#include <std_msgs/Float32.h>
#include "functions.h"
#include <IntervalTimer.h>

volatile int currentfrontLeftCount = INIT;
volatile int currentfrontRightCount = INIT;

volatile int previousfrontLeftCount = INIT;
volatile int previousfrontRightCount = INIT;

volatile bool publish = false;


IntervalTimer velCalc;

extern std_msgs::Float32  rightcurr_Vel;
extern std_msgs::Float32  leftcurr_Vel;

float leftsidecurr_Vel;
float rightsidecurr_Vel;

//////////////
//Encoder Pin initialization
//Will be setting pins for the front, mid, and back wheels
//to hardware interrupt pins acting on a RISING change
//enabling and disenabling interrupt 
//////////////
void init_encoderCounter(void){
  
    pinMode(L_HALL_CHANNEL, INPUT_PULLUP);
    pinMode(R_HALL_CHANNEL, INPUT_PULLUP);

    attachInterrupt(L_HALL_CHANNEL, frontleftEncoderCount, RISING); //attaching interrupt functions
    attachInterrupt(R_HALL_CHANNEL, frontrightEncoderCount, RISING); //attaching interrupt functions

    pinMode(LEFT_SIDE_DIR,OUTPUT);
    pinMode(L_MOTOR_PWM, OUTPUT);

    pinMode(RIGHT_SIDE_DIR, OUTPUT);
    pinMode(R_MOTOR_PWM, OUTPUT);

    velCalc.begin(calcVelocity, VELOCITY_CALC_TIMER); //Currently set at 100 Hz

}

//////////////
//ISR for left wheel encoder 
//////////////

void frontleftEncoderCount(void){
    currentfrontLeftCount++;
}

///////////////////////////////////////////////////////
//ISR for right wheel encoder 
////////////////////////////////////////////////////////

void frontrightEncoderCount(void){
    currentfrontRightCount++;
}

/* 
Circumference is 2*Pi*r.  Angular velocity is just unit distance per second. 
So how many pulses per revolution, what is the circumference? 
Circumference divided by pulses per revolution = distance per pulse. Measure the time per pulse, 
distance per pulse divided by time per pulse = distance/time. */


void calcVelocity(){ //Calculating at 100Hz sampling

    float frontleftVelocity = NTICK * currentfrontLeftCount; //in m/s so will be a float

    float frontrightVelocity = NTICK * currentfrontRightCount; //in m/s so will be a float

    publish = true;

    leftcurr_Vel.data = frontleftVelocity;
    rightcurr_Vel.data = frontrightVelocity;

    previousfrontLeftCount = currentfrontLeftCount;
    previousfrontRightCount = currentfrontRightCount;
        
    currentfrontLeftCount = INIT;

    currentfrontRightCount = INIT;
  
}