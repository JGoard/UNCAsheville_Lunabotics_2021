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
extern volatile int PID_params[PID_PARAMS];

uint16_t errorAccumulator[ARM_DOF][ACCUM_FULL] = {INIT};
int errorParse = INIT;

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
    int node_dir = 22;
    int node_pwm = 2;
    float error = (targetPose[node] - encoderPositions[node]); 

     switch(node){
        case WRIST:{
            node_dir = WRIST_DIR;
            node_pwm = WRIST_PWM;
            break;
        }
        case ELBOW:{
            node_dir = ELBOW_DIR;
            node_pwm = ELBOW_PWM;
            break;
        }
        case SHOULDER:{
            node_dir = SHOULDER_DIR;
            node_pwm = SHOULDER_PWM;
            break;
        }
        case HIP:{
            node_dir = HIP_DIR;
            node_pwm = HIP_PWM;
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
    
    target_PWM = (int)(PID_params[Kp]*(error/CUI_RES)); //+ (PID_params[Ki]*(arraySum(errorAccumulator[WRIST])/CUI_RES)));
    analogWrite(node_pwm, target_PWM);
}
