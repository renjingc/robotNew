#ifndef __INFRARED_H_
#define __INFRARED_H_

#include "stm32f10x.h"

#define INFRARED_PORT GPIOD
#define INFRARED_CLK     RCC_APB2Periph_GPIOD
#define INFRARED1		GPIO_Pin_0
#define INFRARED2		GPIO_Pin_1
#define INFRARED3		GPIO_Pin_2
#define INFRARED4		GPIO_Pin_3

extern int infraredNum;

void Infrared_Init(void);
void Read_Infrared(void);
#endif
