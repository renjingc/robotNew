#ifndef __WAVE1_H_
#define __WAVE1_H_

#include "stm32f10x.h"


#define WAVE_PORT    GPIOD
#define WAVE_CLK     RCC_APB2Periph_GPIOD
#define WAVE1_TRIG		GPIO_Pin_4
#define WAVE2_TRIG		GPIO_Pin_5
#define WAVE3_TRIG		GPIO_Pin_6
#define WAVE4_TRIG		GPIO_Pin_7

void wave3_Init(void);
void wave3_start(void);

#endif
