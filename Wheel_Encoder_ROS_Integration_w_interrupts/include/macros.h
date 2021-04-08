#ifndef MACROS_H_
#define MACROS_H_

#define INIT 0


///////////////
//Macro Pinouts for  Front Wheel Encoder Chip
///////////////
#define FL_HALL_CHANNEL 2

#define FL_MOTOR_PWM 10
#define FL_MOTOR_DIR 34
#define FL_CURRENTSENSE 24

//////////////
//Macro Pinouts for  Mid Wheel Encoder Chip
//////////////

#define ML_HALL_CHANNEL 16

#define ML_MOTOR_PWM 37
#define ML_MOTOR_DIR 
#define M_CURRENTSENSE 41

/////////////
//Macros Pinouts for  Back Wheel Encoder Chip
/////////////

#define BL_HALL_CHANNEL   25

#define BL_MOTOR_PWM 33
#define BL_MOTOR_DIR
#define BL_CURRENTSENSE 40

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

#define FRONT_VEL_CONST currentfrontCount - previousfrontCount //Does current - past encoder ticks
#define MID_VEL_CONST   currentmidCount - previousmidCount
#define BACK_VEL_CONST  currentbackCount - previousbackCount

#define NTICK 0.053 //Multiply this number by number of ticks per sample 
                    //To get Velocit (m/s)
#define WHEELS_PER_SIDE 3

////////////////



#endif /* MACROS_H_ */
