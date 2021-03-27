#ifndef MACROS_H_
#define MACROS_H_

#define INIT 0


///////////////
//Macro Pinouts for  Front Wheel Encoder Chip
///////////////
#define F_HALL_CHANNEL 2

#define F_MOTOR_PWM 10
#define F_MOTOR_DIR 34
#define F_CURRENTSENSE 24

//////////////
//Macro Pinouts for  Mid Wheel Encoder Chip
//////////////

#define M_HALL_CHANNEL 16

#define M_MOTOR_PWM 37
#define M_MOTOR_DIR 
#define M_CURRENTSENSE 41

/////////////
//Macros Pinouts for  Back Wheel Encoder Chip
/////////////

#define B_HALL_CHANNEL   25

#define B_MOTOR_PWM 33
#define B_MOTOR_DIR
#define B_CURRENTSENSE 40

//////////////
//Macros for ROS
//////////////

#define ROS_BAUD 57600

//////////////
//Macros for velocity calc
//////////////

#define CIRCUMFERENCE 2*pi*0.15 //2pi * 0.15 meters is total perimeter of wheel
#define PULSES 300 //Due to it being measured as a rising edge, if otherwise such as changing, it would be 600
#define DIST_PER_PULSE .00314159 //Amount of distance per pulse .003141 meters/pulse... Circum/Pulse
#define VELOCITY_CALC_TIMER 10000 //100 HZ
#define VELOCITY_TIME_DIVIDER 100

////////////////



#endif /* MACROS_H_ */
