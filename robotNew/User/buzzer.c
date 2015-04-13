#include "buzzer.h"

void buzzerInit(void)
{
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启GPIOC的外部时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE); 

		/*选择要控制的GPIOB引脚*/															   
		GPIO_InitStructure.GPIO_Pin = BUZZER;	

		/*选择引脚模式为推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*选择引脚速度50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*初始化GPIOB*/
		GPIO_Init(BUZZER__PORT, &GPIO_InitStructure);			  

		/*设置GPIOB5为1*/
		GPIO_SetBits(BUZZER__PORT, BUZZER);	
}
