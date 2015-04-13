#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "stm32f10x.h"

#define UART1	0
#define UART2	1
void OutPut_Data(void);
extern float OutData[4];
extern float OutData_Uart[6];

#endif /* PROTOCOL_H_ */
