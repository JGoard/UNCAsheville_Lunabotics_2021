
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


#define HIGHBYTE_MASK 16383

#define ENCODER_TIME_POLL 100000
#define ENCODERS_CYCLED encoderNodeCounter == 4

#define TURN_OFF 0

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


/* 24- Motor 2 Current Sensor
25- Motor 3 Current Sensor
26- Motor 4 Current Sensor
27- Motor 1 Current Sensor */


#define ARM_DOF         4

#define WRIST           0
#define WRIST_CHAR      'T' //0x50
#define WRIST_PWM      9 
#define WRIST_DIR      6 
#define WRIST_CS       24
#define WRIST_LOW_LIMIT 1100
#define WRIST_HIGH_LIMIT 3000
#define WRIST_LOW_LIMIT_COMP (joint_goal.data > WRIST_LOW_LIMIT)
#define WRIST_HIGH_LIMIT_COMP (joint_goal.data < WRIST_HIGH_LIMIT)
#define WRIST_LIMIT ((WRIST_LOW_LIMIT_COMP) && (WRIST_HIGH_LIMIT_COMP))

#define ELBOW           1
#define ELBOW_CHAR      'P' //0x54
#define ELBOW_PWM       11
#define ELBOW_DIR       5
#define ELBOW_CS        25
#define ELBOW_LOW_LIMIT 1100
#define ELBOW_HIGH_LIMIT 3000
#define ELBOW_LOW_LIMIT_COMP (joint_goal.data  > ELBOW_LOW_LIMIT)
#define ELBOW_HIGH_LIMIT_COMP (joint_goal.data < ELBOW_HIGH_LIMIT)
#define ELBOW_LIMIT ((ELBOW_LOW_LIMIT_COMP) && (ELBOW_HIGH_LIMIT_COMP))                                                                                                                                                                                                              

#define SHOULDER        2
#define SHOULDER_CHAR   'X' //0x58
#define SHOULDER_PWM    10
#define SHOULDER_DIR     7
#define SHOULDER_CS     26
#define SHOULDER_LOW_LIMIT 1100
#define SHOULDER_HIGH_LIMIT 3000
#define SHOULDER_LOW_LIMIT_COMP (joint_goal.data > SHOULDER_LOW_LIMIT)
#define SHOULDER_HIGH_LIMIT_COMP (joint_goal.data < SHOULDER_HIGH_LIMIT)
#define SHOULDER_LIMIT ((SHOULDER_LOW_LIMIT_COMP) && (SHOULDER_HIGH_LIMIT_COMP))

#define HIP              3
#define HIP_CHAR        'L' //0x4C
#define HIP_PWM          12
#define HIP_DIR          8
#define HIP_CS          27
#define HIP_LOW_LIMIT 1100
#define HIP_HIGH_LIMIT 3000
#define HIP_LOW_LIMIT_COMP (joint_goal.data  > HIP_LOW_LIMIT)
#define HIP_HIGH_LIMIT_COMP (joint_goal.data  < HIP_HIGH_LIMIT)
#define HIP_LIMIT ((HIP_LOW_LIMIT_COMP) && (HIP_HIGH_LIMIT_COMP))

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
