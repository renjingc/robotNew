#include "usart1.h"
#include "led.h"
#include "delay.h"
#include "wave3.h"
#include "time.h"
/*
 *ʹ�����벶��ģʽ
 *TRIG��PC8
 *ECHO��PB6
 */
void wave3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
  	RCC_APB2PeriphClockCmd(WAVE_CLK|RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=WAVE1_TRIG|WAVE2_TRIG|WAVE3_TRIG|WAVE4_TRIG;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;							//�������
	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(WAVE_PORT,WAVE1_TRIG);
	GPIO_ResetBits(WAVE_PORT,WAVE2_TRIG);
	GPIO_ResetBits(WAVE_PORT,WAVE3_TRIG);
	GPIO_ResetBits(WAVE_PORT,WAVE4_TRIG);
	
//	GPIO_InitStructure.GPIO_Pin=WAVE_ECHO;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;									//��������
//	GPIO_Init(WAVE_PORT,&GPIO_InitStructure);
	Time4_Init(0xffff,72-1);   //10Khz�ļ���Ƶ��
}

void wave3_start(void)
{
	  GPIO_SetBits(WAVE_PORT,WAVE1_TRIG); 		  									//��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
		GPIO_SetBits(WAVE_PORT,WAVE2_TRIG);
		GPIO_SetBits(WAVE_PORT,WAVE3_TRIG);
		GPIO_SetBits(WAVE_PORT,WAVE4_TRIG);
		Delay_us(20);		                      										//��ʱ20US
		GPIO_ResetBits(WAVE_PORT,WAVE1_TRIG);
		GPIO_ResetBits(WAVE_PORT,WAVE2_TRIG);
		GPIO_ResetBits(WAVE_PORT,WAVE3_TRIG);
		GPIO_ResetBits(WAVE_PORT,WAVE4_TRIG);
}
