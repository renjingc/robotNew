#ifndef __Wave_H
#define	__Wave_H

#include "stm32f10x.h"

#define	TRIG_PORT      GPIOC		//TRIG       
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_8   //TRIG       
#define	ECHO_PIN       GPIO_Pin_7	//ECHO   

void UltrasonicWave_Configuration(void);               //?????????
void UltrasonicWave_StartMeasure(void);                //????,????>10us???,????????????

#endif /* __UltrasonicWave_H */

