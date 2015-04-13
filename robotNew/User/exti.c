/**********************************************************
配置Exti  这里设置PA0为EXTI

1.设置RCC的AFIO,IO复用的时钟
2.配置NVIC,中断控制器，中断优先级
	1.选择NVIC组别0-4
	2.配置NVIC中断源
	3.设置抢占的优先级
	4.设置响应的优先级
	5.使能NVIC
	6.初始化NVIC
3.配置EXTI  GPIO_EXTILineConfig(A,B,C,D,E,F,G口,Pin)
4.配置EXTI连接到EXTI_Line0上
5.配置EXTI中断模式
6.配置EXTI触发模式
7.使能EXTI
8.初始化EXTI函数

9.在stm32f10x_it.c中编写中断函数
**********************************************************/
#include "exti.h"

void EXTI_PC7_Config()
{
  	GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;


  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//??jtag

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);

		//init GPIOC.7	  
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);


		//GPIOC.7
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

  
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//?????????????
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//?????4?,?16?
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//?????0?,????4?
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//????????
  	NVIC_Init(&NVIC_InitStructure);  	
}
