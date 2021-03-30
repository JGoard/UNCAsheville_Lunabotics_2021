#include <Arduino.h>
#include <ros.h>
#include <arm_handler/arm_msg.h>
#include "macros.h"
#include "functions.h"
#include <string.h>


extern ros::NodeHandle nh;
extern volatile arm_handler::arm_msg arm_pose;

extern volatile uint16_t encoderPositions[ARM_DOF];
extern volatile uint16_t targetPose [ARM_DOF];

uint16_t errorAccumulator[ARM_DOF][ACCUM_FULL] = {INIT};
int errorParse = INIT;

extern volatile bool armSafe;

//char Dec_to_Char[8]; 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: arraySum
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float arraySum (uint16_t array[ACCUM_FULL]){
    float arraySum = INIT;
    for (int i = INIT; i < ACCUM_FULL; i++){
        arraySum += array[i];
    }
     return arraySum;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: PI_control
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PI_control(int node){ 
    int target_PWM;
    int node_dir;
    int node_pwm;
    float error = (targetPose[node] - encoderPositions[node]); 

     switch(node){
        case WRIST:{
            node_dir = WRIST_DIR;
            node_pwm = WRIST_PWM;
            //nh.logwarn("WRIST");
            break;
        }
        case ELBOW:{
            node_dir = ELBOW_DIR;
            node_pwm = ELBOW_PWM;
            //nh.logwarn("ELBOW");
            break;
        }
        case SHOULDER:{
            node_dir = SHOULDER_DIR;
            node_pwm = SHOULDER_PWM;
            //nh.logwarn("SHOULDER");
            break;
        }
        case HIP:{
            node_dir = HIP_DIR;
            node_pwm = HIP_PWM;
            //nh.logwarn("HIP");
            break;
        }
     }
    if (error < INIT) {       
        // pin config for cw rotation
        digitalWrite(node_dir, LOW);
        error = -error;     
    }
    else{
        // pin config for ccw rotation
        digitalWrite(node_dir, HIGH);
    }
    
    errorAccumulator[node][errorParse++] = int(error);

    if (errorParse == ACCUM_FULL) {
        errorParse = INIT;
    }
    
    target_PWM = (int)(Kp*error + Ki*arraySum(errorAccumulator[WRIST]));
    analogWrite(node_pwm, target_PWM);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: Turns off write to arm and locks up
// MCU until reset
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void armcurrentProtection(){

 for (int node = WRIST_PWM; node  <= HIP_PWM; node++)
    {
       analogWrite(node, TURN_OFF);

    }



}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Header: Monitors current of arm
//
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void monitorarmCurrent(){

    int armCurs[ARM_DOF];

    armCurs[WRIST] = analogRead(); //Wrist //Need to inclide Analog reads for current sense pins here
    armCurs[ELBOW] = analogRead(); //Elbow
    armCurs[SHOULDER] = analogRead(); //Shoulder
    armCurs[HIP] = analogRead(); //Hip 

    for (int node = INIT; node  <= ARM_DOF; node++)
        {
            if (armCurs[node] == FAULT_CURRENT){
                armSafe = false; //turns off all arms and encoders
            }
        }
    

}