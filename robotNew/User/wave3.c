#include "usart1.h"
#include "led.h"
#include "delay.h"
#include "wave3.h"
#include "time.h"
/*
 *使用输入捕获模式
 *TRIG接PC8
 *ECHO接PB6
 */
void wave3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
  	RCC_APB2PeriphClockCmd(WAVE_CLK|RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=WAVE1_TRIG|WAVE2_TRIG|WAVE3_TRIG|WAVE4_TRIG;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;							//推挽输出
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(WAVE_PORT,WAVE1_TRIG);
	GPIO_ResetBits(WAVE_PORT,WAVE2_TRIG);
	GPIO_ResetBits(WAVE_PORT,WAVE3_TRIG);
	GPIO_ResetBits(WAVE_PORT,WAVE4_TRIG);
	
//	GPIO_InitStructure.GPIO_Pin=WAVE_ECHO;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;									//下拉输入
//	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	Time4_Init(0xffff,72-1);   //10Khz的计数频率
}

void wave3_start(void)
{
	  GPIO_SetBits(WAVE_PORT,WAVE1_TRIG); 		  									//送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
		GPIO_SetBits(WAVE_PORT,WAVE2_TRIG);
		GPIO_SetBits(WAVE_PORT,WAVE3_TRIG);
		GPIO_SetBits(WAVE_PORT,WAVE4_TRIG);
		Delay_us(20);		                      										//延时20US
		GPIO_ResetBits(WAVE_PORT,WAVE1_TRIG);
		GPIO_ResetBits(WAVE_PORT,WAVE2_TRIG);
		GPIO_ResetBits(WAVE_PORT,WAVE3_TRIG);
		GPIO_ResetBits(WAVE_PORT,WAVE4_TRIG);
}
