
#ifndef MACROS_H_
#define MACROS_H_


//MACROS FOR PINS TAKEN ON TEENSY

#define RX        0  //These two pins are for the RS-485 
#define TX        1  //Implementation on the board for encoders

#define WRIST_PWM 
#define ELBOW_PWM
#define SHOULDER_PWM
#define HIP_PWM



//MACROS FOR STATES AND OTHER FUNKY NUMBERS
#define INIT  0

#define RXBACK 0
#define LOWBYTE 1
#define HIGHBYTE 2
#define PUBLISH_ENCODER 3
#define PUBLISH transStatus == 3
#define TRANS_END 3

#define SHIFT_RES 2

#define FREQ 100

#define HIGHBYTE_MASK 16383

#define ENCODER_TIME_POLL 1000


//#define RxTx 3
#define Re    3
#define De   5

#define Transmit    HIGH
#define Receive     LOW

#define Pin13LED         13

#define WRIST       'T' //0x50
#define ELBOW       'P' //0x54
#define SHOULDER    'X' //0x58
#define HIP         'L' //0x4C
#define ENCODERS_CYCLED encoderNodeCounter == 4

#define WRIST_PWM
#define ELBOW_PWM
#define SHOULDER_PWM
#define HIP_PWM

/* #define Kp 20
#define Ki 10
#define Kd 0 */

#define ARM_DOF 4

#endif /* MACROS_H_ */
