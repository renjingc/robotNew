/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "led.h"
#include "delay.h"
#include "wave.h"
#include "usart1.h"
#include "wave3.h"

extern float UltrasonicWave_Distance;  

extern void TimingDelay_Decrement(void);
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
//void EXTI0_IRQHandler()
//{
//	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//ȷ���Ƿ������EXTI_Line0�ж�
//	{
//		LED1_TOGGLE
//		EXTI_ClearITPendingBit(EXTI_Line0);//���жϱ�־λ
//	}
//}
//void TIM2_IRQHandler(void)   //TIM2�ж�
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//	}
//}

//void EXTI9_5_IRQHandler(void)
//{
//	Delay_us(10);		                      											//��ʱ10us
//  if(EXTI_GetITStatus(EXTI_Line7) != RESET)
//	{
//			TIM_SetCounter(TIM2,0);
//			TIM_Cmd(TIM2, ENABLE);                                  //����ʱ��
//			
//			while(GPIO_ReadInputDataBit(WAVE_PORT ,WAVE_ECHO));	    //�ȴ��͵�ƽ
//			
//			TIM_Cmd(TIM2, DISABLE);			                            //��ʱ��2ʧ��
//			UltrasonicWave_Distance=TIM_GetCounter(TIM2)*5*34/200.0;									 		//�������&&UltrasonicWave_Distance<150
//		
//		if(UltrasonicWave_Distance>0)
//		{
//			printf("distance:%f cm",UltrasonicWave_Distance);
//		}
//		EXTI_ClearITPendingBit(EXTI_Line7);  											//���EXTI7��·����λ
//	}
//}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
