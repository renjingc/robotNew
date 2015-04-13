/*************************************
led�����ļ�
PB0--LED1

1.GPIOʹ�÷��� ����һ��GPIO_InitTypeDef���ͽṹ��
2.����GPIOC���ⲿʱ��
3.ѡ��GPIO������
4.ѡ��GPIO��ģʽ
5.ѡ��GPIO���ٶ�
6.����GPIO,GPIO_SetBitsΪ��1��GPIO_ResetBitsΪ��0
**************************************/
#include "led.h"

void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����GPIOC���ⲿʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	

		/*ѡ������ģʽΪ�������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*ѡ�������ٶ�50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*��ʼ��GPIOB*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);			  

		/*����GPIOB0Ϊ1*/
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
