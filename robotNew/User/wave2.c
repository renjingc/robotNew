#include "usart1.h"
#include "led.h"
#include "delay.h"
#include "wave2.h"

/*
 *使用EXTI中断模式
 */
float UltrasonicWave_Distance;      //计算出的距离 
void wave2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(WAVE_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=WAVE_TRIG;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;							//推挽输出
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(WAVE_PORT,WAVE_TRIG);
	
	GPIO_InitStructure.GPIO_Pin=WAVE_ECHO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;									//下拉输入
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);															//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;										//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;								//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;										//子优先级2 
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;											//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  													//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void wave2_start(void)
{
	GPIO_SetBits(WAVE_PORT,WAVE_TRIG); 		  									//送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
	Delay_us(20);		                      										//延时20US
	GPIO_ResetBits(WAVE_PORT,WAVE_TRIG);
}
