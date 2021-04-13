#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>
#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;
std_msgs::Float32 rightsidecurr_Vel;
std_msgs::Float32 leftsidecurr_Vel;
ros::Publisher leftvelPub("wheelCount", &leftsideVel);
ros::Publisher rightvelPub("wheelCount", &rightsideVel);


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

    leftvelPub.publish(&leftsidecurr_Vel); //publishes only frontCount currently
    rightvelPub.publish(&rightsidecurr_Vel); 
        delay(3);
        nh.spinOnce();


}

