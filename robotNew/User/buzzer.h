#ifndef __BUZZER_H
#define	__BUZZER_H

#include "stm32f10x.h"

#define BUZZER__PORT   GPIOB
#define BUZZER		   GPIO_Pin_5


void buzzerInit(void);

#endif
