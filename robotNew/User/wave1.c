#include "usart1.h"
#include "led.h"
#include "delay.h"
#include "wave1.h"
/*
 *使用while循环等待模式	
 **/
void wave1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(WAVE_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=WAVE_TRIG;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	//推挽输出
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(WAVE_PORT,WAVE_TRIG);
	
	GPIO_InitStructure.GPIO_Pin=WAVE_ECHO;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
}

void wave1_start(float *d)
{
	uint8_t i;
	uint32_t j;
	float temp=0;
	for(i=0;i<5;i++)
	{
		GPIO_SetBits(WAVE_PORT,WAVE_TRIG);
		Delay_us(20);
		GPIO_ResetBits(WAVE_PORT,WAVE_TRIG);
		while(!GPIO_ReadInputDataBit(WAVE_PORT,WAVE_ECHO));
		while(GPIO_ReadInputDataBit(WAVE_PORT,WAVE_ECHO))
		{
			Delay_us(10);
			j++;
		}
		temp+=340/2*j*10;
		j=0;
		Delay_ms(60);//防止发射信号对回响信号的影响
	}
	*d=temp/5/100000;
}
