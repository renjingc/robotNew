#include "usart1.h"
#include "led.h"
#include "delay.h"
#include "wave2.h"

/*
 *ʹ��EXTI�ж�ģʽ
 */
float UltrasonicWave_Distance;      //������ľ��� 
void wave2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(WAVE_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=WAVE_TRIG;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;							//�������
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(WAVE_PORT,WAVE_TRIG);
	
	GPIO_InitStructure.GPIO_Pin=WAVE_ECHO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;									//��������
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);															//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;										//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;								//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;										//�����ȼ�2 
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;											//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  													//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

void wave2_start(void)
{
	GPIO_SetBits(WAVE_PORT,WAVE_TRIG); 		  									//��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
	Delay_us(20);		                      										//��ʱ20US
	GPIO_ResetBits(WAVE_PORT,WAVE_TRIG);
}
