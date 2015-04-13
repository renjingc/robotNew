#include "buzzer.h"

void buzzerInit(void)
{
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����GPIOC���ⲿʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
		GPIO_InitStructure.GPIO_Pin = BUZZER;	

		/*ѡ������ģʽΪ�������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*ѡ�������ٶ�50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*��ʼ��GPIOB*/
		GPIO_Init(BUZZER__PORT, &GPIO_InitStructure);			  

		/*����GPIOB5Ϊ1*/
		GPIO_SetBits(BUZZER__PORT, BUZZER);	
}
