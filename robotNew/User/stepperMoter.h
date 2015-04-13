#ifndef __STEPPERMOTER_H_
#define __STEPPERMOTER_H_

#include "stm32f10x.h"

void TIM4GPIO_Init(void);
void Tim4_Configuration(void);
void TIM4_Init(void);

void TIM5GPIO_Init(void);
void Tim5_Configuration(void);
void TIM5_Init(void);


void TIM1GPIO_Init(void);
void Tim1_Configuration(void);
void TIM1_Init(void);

void TIM8GPIO_Init(void);
void Tim8_Configuration(void);
void TIM8_Init(void);

void stepperMoterInit(void);
void setAllSteeringEngine(void);

#endif
