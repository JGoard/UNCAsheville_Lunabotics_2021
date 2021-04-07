
#ifndef MACROS_H_
#define MACROS_H_


//MACROS FOR STATES AND OTHER FUNKY NUMBERS
#define INIT  0

#define RXBACK 0
#define LOWBYTE 1
#define HIGHBYTE 2
#define PUBLISH_ENCODER 3
#define PUBLISH transStatus == 3
#define TRANS_END 3

#define SHIFT_RES 2

#define FREQ 1000000

#define HIGHBYTE_MASK 16383

#define ENCODER_TIME_POLL 10000
#define ENCODERS_CYCLED encoderNodeCounter == 4



#define Transmit    HIGH
#define Receive     LOW

#define Pin13LED        13
#define RS485_BAUD      115200

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//RS485 PIN macros:
#define RX        0  //These two pins are for the RS-485 
#define TX        1  //Implementation on the board for encoders
#define Re        2 
#define De        3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// joint macros:
#define ARM_DOF         4

#define WRIST           0
#define WRIST_CHAR      'T' //0x50
#define WRIST_PWM      9 //11
#define WRIST_DIR      6 // 5

#define ELBOW           1
#define ELBOW_CHAR      'P' //0x54
#define ELBOW_PWM       11//9
#define ELBOW_DIR       5//6

#define SHOULDER        2
#define SHOULDER_CHAR   'X' //0x58
#define SHOULDER_PWM    10
#define SHOULDER_DIR     7

#define HIP              3
#define HIP_CHAR        'L' //0x4C
#define HIP_PWM          12
#define HIP_DIR          8
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~
// PID Macros:

#define Kp 0.0471
#define Ki 0.00
#define Kd 0

#define INIT_POSE    2048

#define PID_PARAMS      3
#define CUI_RES      4096
#define ACCUM_FULL      2
//~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~
// ROS Macros:
#define ROS_BAUD  500000
//~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Accelerometer Macros ISM330DLC
//#define I2C_SDA 18
//#define I2C_SCL 19
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Current sensing macros:
#define FAULT_CURRENT   // ~130mV max reading from CS pin



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif /* MACROS_H_ */
