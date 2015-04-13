#ifndef __WAVE1_H_
#define __WAVE1_H_

#include "stm32f10x.h"


#define WAVE_PORT    GPIOC
#define WAVE_CLK     RCC_APB2Periph_GPIOC
#define WAVE_TRIG		 GPIO_Pin_8
#define WAVE_ECHO    GPIO_Pin_7

void wave2_Init(void);
void wave2_start(void);

#endif
