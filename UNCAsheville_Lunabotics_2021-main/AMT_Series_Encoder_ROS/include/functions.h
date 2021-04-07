//Joshua Goard's RS-485 Work
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void RS485Receive_EN(void);
void RS485Transmit_EN(void);

void RS485Transmit_Addr(void);
void RS485Receive_Pos(void);

void RS485ReceiveParse(void);

void ros_init(void);
void rs485_init(void);
void pollEncoder(void);

void ros_update(void);


#endif /* FUNCTIONS_H_ */
