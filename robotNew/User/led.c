/*************************************
led驱动文件
PB0--LED1

1.GPIO使用方法 定义一个GPIO_InitTypeDef类型结构体
2.开启GPIOC的外部时钟
3.选择GPIO的引脚
4.选择GPIO的模式
5.选择GPIO的速度
6.设置GPIO,GPIO_SetBits为设1，GPIO_ResetBits为设0
**************************************/
#include "led.h"

void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启GPIOC的外部时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

		/*选择要控制的GPIOB引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	

		/*选择引脚模式为推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*选择引脚速度50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*初始化GPIOB*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);			  

		/*设置GPIOB0为1*/
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
