#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>

volatile int currentfrontCount = INIT;
volatile int currentmidCount = INIT;
volatile int currentbackCount = INIT;

volatile int previousfrontCount = INIT;
volatile int previousmidCount = INIT;
volatile int previousbackCount = INIT;


bool printFront = false;
bool printMid = false;
bool printBack = false;
IntervalTimer velCalc;

extern std_msgs::Float32 rightcurr_Vel;
extern std_msgs::Float32 leftcurr_Vel;

std_msgs::Float32 leftsidecurr_Vel;
std_msgs::Float32 rightsidecurr_Vel;

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
                                                               //If resolution would like to be increased, change to CHANGE


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


void calcVelocity(){ //Calculating at 100Hz sampling

    /* frontVelocity = FRONT_VEL_CONSTANT * VELOCITY_SAMPLE_TIME * VEL_PI_CONSTANT;
    midVelocity = MID_VEL_CONSTANT * VELOCITY_SAMPLE_TIME * VEL_PI_CONSTANT;
    backVelocity = BACK_VEL_CONSTANT * VELOCITY_SAMPLE_TIME * VEL_PI_CONSTANT; */

    frontVelocity = NTICK * currentfrontCount; //in m/s so will be a float
    midVelocity = NTICK * currentmidCount;
    backVelocity = NTICK * currentbackCount;
    
    /* FRONT_VEL_CONSTANT/PULSE_PER_METER;
    midVelocity = MID_VEL_CONSTANT/PULSE_PER_METER; 
    backVelocity = BACK_VEL_CONSTANT/PULSE_PER_METER; */

    //Not sure which of the ones to do above would work 
    leftsidecurr_Vel = frontVelocity + midVelocity + backVelocity;
    leftsidecurr_Vel /= WHEELS_PER_SIDE;

    previousfrontCount = currentfrontCount;
    previousmidCount = currentmidCount;
    previousbackCount = currentbackCount;
    
    currentfrontCount = INIT;
    currentmidCount   = INIT;
    currentbackCount  = INIT; 

    
  






}