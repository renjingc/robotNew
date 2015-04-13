/**********************************************************
����Exti  ��������PA0ΪEXTI

1.����RCC��AFIO,IO���õ�ʱ��
2.����NVIC,�жϿ��������ж����ȼ�
	1.ѡ��NVIC���0-4
	2.����NVIC�ж�Դ
	3.������ռ�����ȼ�
	4.������Ӧ�����ȼ�
	5.ʹ��NVIC
	6.��ʼ��NVIC
3.����EXTI  GPIO_EXTILineConfig(A,B,C,D,E,F,G��,Pin)
4.����EXTI���ӵ�EXTI_Line0��
5.����EXTI�ж�ģʽ
6.����EXTI����ģʽ
7.ʹ��EXTI
8.��ʼ��EXTI����

9.��stm32f10x_it.c�б�д�жϺ���
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
