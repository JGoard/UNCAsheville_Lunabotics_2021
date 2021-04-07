#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;
std_msgs::UInt16 wheelCount;
ros::Publisher feedback("wheelCount", &wheelCount);


extern volatile int frontCount;
extern volatile int midCount;
extern volatile int backCount;

extern bool printFront;
extern bool printMid;
extern bool printBack;




void setup() {
    
    init_encoderCounter();
    ros_init();
   //Serial.begin(9600);

}

void loop() {

    if (printFront){
        //Serial.print("Front Count: ");
        //Serial.println(frontCount);
        wheelCount.data = frontCount;
        printFront = false;

    }

    if(printMid){
        //Serial.print("Mid Count: ");
        //Serial.println(midCount);
        printMid = false;
    }

    if(printBack){
        //Serial.print("Back Count: ");
       // Serial.println(backCount);
        printBack = false;
    }


        feedback.publish(&wheelCount); //publishes only frontCount currently
        delay(3);
        nh.spinOnce();


}

