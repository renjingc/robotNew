/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "usart1.h"
#include "time.h"
#include "delay.h"

#include "wave3.h"
#include "pwmMoter.h"
#include "infrared.h"
#include "buzzer.h"
#include "stepperMoter.h"
#include "communication.h"

#include <string.h>
#include <stdio.h>
#include <math.h> 


__IO u8 receive_temp[15], receive_complete_flag = 0;
__IO u8 receive_count = 0;
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */

int main(void)
{
	SysTick_Init();
	USART1_Init();
	//wave3_Init();
	Car_Init();
	buzzerInit();
	Infrared_Init();
	stepperMoterInit();

	printf("start\n");

	while(1)
	{	
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;// 关闭滴答定时器 		
		while(receive_complete_flag == 0)
		{} 
		SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;// 开启滴答定时器 
		communicationProtocol();   
	}
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 
	    receive_temp[receive_count++] = USART1->DR;
	    if(receive_temp[0] != '$' )
		{
			receive_count = 0;
			return;
		}
		if(receive_temp[receive_count-1] == '#')//接收完毕
		{
			receive_complete_flag = 1;
			//receive_count = 0;
      	}     
	} 	 
}
/*********************************************END OF FILE**********************/

