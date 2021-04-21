#include <Arduino.h>
#include "macros.h"
#include <std_msgs/Float32.h>
#include "functions.h"
#include <IntervalTimer.h>

volatile int currentfrontLeftCount = INIT;
volatile int currentmidLeftCount = INIT;
volatile int currentbackLeftCount = INIT;

volatile int currentfrontRightCount = INIT;
volatile int currentmidRightCount = INIT;
volatile int currentbackRightCount = INIT;

volatile int previousfrontCount = INIT;
volatile int previousmidCount = INIT;
volatile int previousbackCount = INIT;
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
  
   pinMode(FL_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(ML_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(BL_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(FR_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(MR_HALL_CHANNEL, INPUT_PULLUP);
   pinMode(BR_HALL_CHANNEL, INPUT_PULLUP);


   attachInterrupt(FL_HALL_CHANNEL, frontleftEncoderCount, RISING); //attaching interrupt functions to 
   attachInterrupt(ML_HALL_CHANNEL, midleftEncoderCount, RISING);   //these pins
   attachInterrupt(BL_HALL_CHANNEL, backleftEncoderCount, RISING);  //Currently, these wheels will spin 900 counts
   attachInterrupt(FR_HALL_CHANNEL, frontrightEncoderCount, RISING); //attaching interrupt functions to 
   attachInterrupt(MR_HALL_CHANNEL, midrightEncoderCount, RISING);   //these pins
   attachInterrupt(BR_HALL_CHANNEL, backrightEncoderCount, RISING);                                                            //per revolution
                                                               //If resolution would like to be increased, change to CHANGE

                                         //Currently, these wheels will spin 900 counts
                                                               //per revolution
                                                               //If resolution would like to be increased, change to CHANGE 
    pinMode(LEFT_SIDE_DIR,OUTPUT);
    pinMode(FL_MOTOR_PWM, OUTPUT);
    pinMode(ML_MOTOR_PWM, OUTPUT);
    pinMode(BL_MOTOR_PWM, OUTPUT);

    pinMode(RIGHT_SIDE_DIR, OUTPUT);
    pinMode(FR_MOTOR_PWM, OUTPUT);
    pinMode(MR_MOTOR_PWM, OUTPUT);
    pinMode(BR_MOTOR_PWM, OUTPUT);





/*     digitalWrite(FL_MOTOR_PWM,100);
    digitalWrite(ML_MOTOR_PWM,100);
    digitalWrite(BL_MOTOR_PWM,100);

    digitalWrite(FR_MOTOR_PWM,100);
    digitalWrite(MR_MOTOR_PWM,100);
    digitalWrite(BR_MOTOR_PWM,100); */

    velCalc.begin(calcVelocity, VELOCITY_CALC_TIMER); //Currently set at 100 Hz

}

//////////////
//ISR for front wheel encoder 
//////////////

void frontleftEncoderCount(void){
currentfrontLeftCount++;
    

}

//////////////
//ISR for mid wheel encoder
//////////////

void midleftEncoderCount(void){
currentmidLeftCount++;
}

//////////////
//ISR for back wheel encoder
//////////////

void backleftEncoderCount(void){
currentbackLeftCount++;
}

///////////////////////////////////////////////////////
//ISR for front wheel encoder 
////////////////////////////////////////////////////////

void frontrightEncoderCount(void){
currentfrontRightCount++;
    

}

//////////////
//ISR for mid wheel encoder
//////////////

void midrightEncoderCount(void){
currentmidRightCount++;
}

//////////////
//ISR for back wheel encoder
//////////////

void backrightEncoderCount(void){
currentbackRightCount++;
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

   float frontleftVelocity = NTICK * currentfrontLeftCount; //in m/s so will be a float
   float midleftVelocity = NTICK * currentmidLeftCount;
   float backleftVelocity = NTICK * currentbackLeftCount;

   float frontrightVelocity = NTICK * currentfrontRightCount; //in m/s so will be a float
   float midrightVelocity = NTICK * currentmidRightCount;
   float backrightVelocity = NTICK * currentbackRightCount;
   publish = true;
    
    /* FRONT_VEL_CONSTANT/PULSE_PER_METER;
    midVelocity = MID_VEL_CONSTANT/PULSE_PER_METER; 
    backVelocity = BACK_VEL_CONSTANT/PULSE_PER_METER; */

    //Not sure which of the ones to do above would work 
    leftsidecurr_Vel = frontleftVelocity + midleftVelocity + backleftVelocity;
    leftsidecurr_Vel = leftsidecurr_Vel / WHEELS_PER_SIDE;

    rightsidecurr_Vel = frontrightVelocity + midrightVelocity + backrightVelocity;
    rightsidecurr_Vel = rightsidecurr_Vel / WHEELS_PER_SIDE;

    leftcurr_Vel.data = leftsidecurr_Vel;
    rightcurr_Vel.data = rightsidecurr_Vel;

    previousfrontCount = currentfrontLeftCount;
    previousmidCount = currentmidLeftCount;
    previousbackCount = currentbackLeftCount;

        
    currentfrontLeftCount = INIT;
    currentmidLeftCount   = INIT;
    currentbackLeftCount  = INIT; 

    currentfrontRightCount = INIT;
    currentmidRightCount   = INIT;
    currentbackRightCount  = INIT; 
  






}