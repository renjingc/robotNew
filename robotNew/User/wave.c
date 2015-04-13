

#include "wave.h"
#include "usart1.h"
#include "time.h"
#include "delay.h"




float UltrasonicWave_Distance;      //??????    


/*
 * ???:UltrasonicWave_Configuration
 * ??  :?????????
 * ??  :?
 * ??  :?	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//??jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC8?TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //????????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //?????GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC7?ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //????
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //???GPIOA
	
	 //GPIOC.7	  ????????????
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

 	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//??EXTI_InitStruct???????????EXTI???
		
			
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//?????????????
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//?????2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//????2 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//????????
  NVIC_Init(&NVIC_InitStructure);  	  //??NVIC_InitStruct???????????NVIC???
}




/*
 * ???:UltrasonicWave_StartMeasure
 * ??  :????,????>10us???,????????????
 * ??  :?
 * ??  :?	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //?>10US?????RIG_PORT,TRIG_PIN????define???
  Delay_us(20);		                      //??20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
}

/******************* (C) 1209 Lab *****END OF FILE************/
