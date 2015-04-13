#ifndef __BUZZER_H
#define	__BUZZER_H

#include "stm32f10x.h"

#define BUZZER__PORT   GPIOE
#define BUZZER		   GPIO_Pin_4


void buzzerInit(void);

#endif
