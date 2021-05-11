#ifndef MACROS_H_
#define MACROS_H_

#define INIT 0
#define PUBLISH publish = true

///////////////
//Macro Pinouts for  Front Left Wheel Encoder Chip
///////////////
#define LEFT_SIDE_DIR 34


#define L_HALL_CHANNEL 2

#define L_MOTOR_PWM 10
#define FL_CURRENTSENSE 24

//////////////
//Macro Pinouts for  Mid Left Wheel Encoder Chip
//////////////

#define ML_HALL_CHANNEL 16

#define ML_MOTOR_PWM 11
#define M_CURRENTSENSE 41

/////////////
//Macros Pinouts for  Back Left Wheel Encoder Chip
/////////////

#define BL_HALL_CHANNEL   25

#define BL_MOTOR_PWM 33
#define BL_CURRENTSENSE 40

///////////////
//Macro Pinouts for  Front Right Wheel Encoder Chip
///////////////
#define RIGHT_SIDE_DIR 0


#define R_HALL_CHANNEL 3

#define R_MOTOR_PWM 8
#define FR_CURRENTSENSE 

//////////////
//Macro Pinouts for  Mid Left Wheel Encoder Chip
//////////////

#define MR_HALL_CHANNEL 4

#define MR_MOTOR_PWM 7
#define MR_CURRENTSENSE 

/////////////
//Macros Pinouts for  Back Left Wheel Encoder Chip
/////////////

#define BR_HALL_CHANNEL 5

#define BR_MOTOR_PWM 6
#define B_CURRENTSENSE 

//////////////
//Macros for ROS
//////////////

#define ROS_BAUD 57600

//////////////
//Macros for velocity calc
//////////////

#define VEL_PI_CONSTANT pi*.75^2 //R*PI /180
#define PULSES_PER_REV 900 //Due to it being measured as a rising edge, if otherwise such as changing, it would be 600
#define METER_PER_PULSE .00314159 //Amount of distance per pulse .003141 meters/pulse... MPP = Circum/Pulse
#define PULSE_PER_METER 318.36 //These are how many pulses there will be in a meters worth of travel for each wheel based off of rising edge
#define VELOCITY_CALC_TIMER 10000 //100 HZ
#define VELOCITY_SAMPLE_TIME 100 //Used for time elapsed since encoders were last polled
                                 // (current - past) / 1/100 == (current - past) * 100

#define FRONT_VEL_CONST currentfrontLeftCount - previousfrontCount //Does current - past encoder ticks
#define MID_VEL_CONST   currentmidLeftCount - previousmidCount
#define BACK_VEL_CONST  currentbackLeftCount - previousbackCount

#define NTICK 0.053 //Multiply this number by number of ticks per sample 
                    //To get Velocit (m/s)
#define WHEELS_PER_SIDE 3

////////////////



#endif /* MACROS_H_ */
