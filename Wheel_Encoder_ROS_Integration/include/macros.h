#ifndef MACROS_H_
#define MACROS_H_

#define INIT 0


///////////////
//Macro Pinouts for  Front Wheel Encoder Chip
///////////////
#define CCLR_F   0
#define CCKEN_F  1

#define BITF_0   2
#define BITF_1   3
#define BITF_2   4
#define BITF_3   5
#define BITF_4   6
#define BITF_5   7
#define BITF_6   8
#define BITF_7   9

#define F_MOTOR_PWM 10
#define F_CURRENTSENSE 24

//////////////
//Macro Pinouts for  Mid Wheel Encoder Chip
//////////////
#define CCLR_M   11
#define CCKEN_M  12

#define BITM_0   16
#define BITM_1   17
#define BITM_2   18
#define BITM_3   19
#define BITM_4   20
#define BITM_5   21
#define BITM_6   22
#define BITM_7   23

#define M_MOTOR_PWM 37
#define M_CURRENTSENSE 41

/////////////
//Macros Pinouts for  Back Wheel Encoder Chip
/////////////
#define CCLR_B 35
#define CCKEN_B 36

#define BITB_0   25
#define BITB_1   26
#define BITB_2   27
#define BITB_3   28
#define BITB_4   29
#define BITB_5   30
#define BITB_6   31
#define BITB_7   32

#define B_MOTOR_PWM 33
#define B_CURRENTSENSE 40


////////////////
#define ONES 1
#define TWOS 2
#define THREES 4
#define FOURS 8
#define FIVES 16
#define SIXTHS 32
#define SEVENTHS 64
#define EIGHTHS 128


#endif /* MACROS_H_ */
