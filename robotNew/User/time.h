#ifndef __TIMER_H
#define __TIMER_H  

#include "stm32f10x.h"

extern uint32_t timeUp1;
extern uint32_t timeUp2;
extern uint32_t timeUp3;
extern uint32_t timeUp4;

void Time_Init(uint16_t arr,uint16_t psc); 
void Time4_Init(uint16_t arr,uint16_t psc);
void Time2_Init(uint16_t arr, uint16_t psc);
#endif
