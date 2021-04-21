#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>
#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;
std_msgs::Float32 rightcurr_Vel;
std_msgs::Float32 leftcurr_Vel;

ros::Publisher leftvelPub("LeftPubVel", &leftcurr_Vel);
ros::Publisher rightvelPub("RightPubVel", &rightcurr_Vel);


extern volatile int currentfrontLeftCount;
extern volatile int currentmidLeftCount;
extern volatile int currentbackLeftCount;
extern volatile bool publish;

extern bool printFront;
extern bool printMid;
extern bool printBack;




void setup() {
    
    init_encoderCounter();
    ros_init();

}

void loop() {


    if(publish){
    leftvelPub.publish(&leftcurr_Vel); //publishes only FL
    rightvelPub.publish(&rightcurr_Vel); 
        delay(3);
        nh.spinOnce(); 
        publish = false;
    }

}

