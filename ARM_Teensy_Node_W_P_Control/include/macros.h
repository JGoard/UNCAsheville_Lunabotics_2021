
#ifndef MACROS_H_
#define MACROS_H_


//MACROS FOR PINS TAKEN ON TEENSY

#define RX        0  //These two pins are for the RS-485 
#define TX        1  //Implementation on the board for encoders


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

//#define RxTx 3
#define Re    3 
#define De    5

#define Transmit    HIGH
#define Receive     LOW

#define Pin13LED        13
#define RS485_BAUD      115200
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// joint macros:
#define ARM_DOF         4

#define WRIST           0
#define WRIST_CHAR      'T' //0x50
#define WRIST_PWM       2
#define WRIST_DIR       22

#define ELBOW           1
#define ELBOW_CHAR      'P' //0x54
#define ELBOW_PWM  10//TBD 
#define ELBOW_DIR  11//TBD

#define SHOULDER        2
#define SHOULDER_CHAR   'X' //0x58
#define SHOULDER_PWM 12//TBD
#define SHOULDER_DIR 13//TBD

#define HIP             3
#define HIP_CHAR        'L' //0x4C
#define HIP_PWM 14//TBD
#define HIP_DIR 15//TBD
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~
// PID Macros:
#define Kp_INIT      275
#define Ki_INIT      10
#define Kd_INIT      0

#define Kp 0
#define Ki 1
#define Kd 2

#define PID_PARAMS      3
#define CUI_RES      4096
#define ACCUM_FULL      2
//~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~
// ROS Macros:
#define ROS_BAUD  57600
//~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Accelerometer Macros ISM330DLC
//#define I2C_SDA 18
//#define I2C_SCL 19
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif /* MACROS_H_ */
