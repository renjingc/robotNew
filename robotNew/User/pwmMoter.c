#include "pwmMoter.h"
#include "delay.h"
#include "time.h"
int moterState=0;
void TIM3GPIO_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	/* GPIOA and GPIOB clock enable */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

  	/*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
void CarGPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		/*����GPIOC���ⲿʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 
		/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		/*ѡ�������ٶ�50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		/*��ʼ��GPIOB*/
		GPIO_Init(GPIOC, &GPIO_InitStructure);	

		GPIO_SetBits(GPIOC,GPIO_Pin_0);
  		GPIO_SetBits(GPIOC,GPIO_Pin_1);
  		GPIO_SetBits(GPIOC,GPIO_Pin_2);
  		GPIO_SetBits(GPIOC,GPIO_Pin_3);	
}
void Tim3_Configuration(void)
{
	/*
	 *PWM��ʼ��
	 */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
	/* PWM�źŵ�ƽ����ֵ */
 	u16 CCR1_Val = 700;      //ǰ��ĵ��
 	u16 CCR2_Val = 700;	  	 //����ĵ��
 	u16 CCR3_Val = 700;		 //����ĵ��
 	u16 CCR4_Val = 700;		 //����ĵ��

	/* ����TIM3CLK Ϊ 72MHZ */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	
/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 6;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
}
void Car_Init(void)
{
	TIM3GPIO_Init();
	Tim3_Configuration();
	CarGPIO_Init();	
}

//moter1Ϊǰ��ĵ��
void motor1(uint8_t dir, uint8_t state,int speed_add)
{
	if(state  == 0)//ֹͣ
	{
		TIM_SetCompare1(TIM3,0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		return;
  	}
	if(dir)//Ϊ1����ת
	{
		TIM_SetCompare1(TIM3,400-(MORTOR_SPEED+speed_add));
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
  	}
	else
	{
		TIM_SetCompare1(TIM3,600+(MORTOR_SPEED+speed_add));
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
  	}
}
//moter2Ϊ����ĵ��
void motor2(uint8_t dir, uint8_t state,int speed_add)
{
	if(state  == 0)//ֹͣ
	{
		TIM_SetCompare2(TIM3,0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		return;
  	}
	if(dir)//Ϊ1����ת
	{
		TIM_SetCompare2(TIM3,400-(MORTOR_SPEED+speed_add));
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
  	}
	else
	{
		TIM_SetCompare2(TIM3,600+(MORTOR_SPEED+speed_add));
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
  	}
}
//moter3Ϊ����ĵ��
void motor3(uint8_t dir, uint8_t state,int speed_add)
{
	if(state  == 0)//ֹͣ
	{
		TIM_SetCompare3(TIM3,0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
		return;
  	}
	if(dir)//Ϊ1����ת
	{
		TIM_SetCompare3(TIM3,400-(MORTOR_SPEED+speed_add));
		GPIO_SetBits(GPIOC,GPIO_Pin_2);
  	}
	else
	{
		TIM_SetCompare3(TIM3,600+(MORTOR_SPEED+speed_add));
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
  	}
}
//moter4Ϊ����ĵ��
void motor4(uint8_t dir, uint8_t state,int speed_add)
{
	if(state  == 0)//ֹͣ
	{
		TIM_SetCompare4(TIM3,0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		return;
  	}
	if(dir)//Ϊ1����ת
	{
		TIM_SetCompare4(TIM3,400-(MORTOR_SPEED+speed_add));
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
  	}
	else
	{
		TIM_SetCompare4(TIM3,600+(MORTOR_SPEED+speed_add));
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
  	}
}
//speed��0-999��
void motor_straight(int speed)
{
	motor3(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor4(ZHENG_ZHUAN,MORTOR_START,speed-800);
	moterState=1;
}
void motor_back(int speed)
{
	motor3(FAN_ZHUAN,MORTOR_START,speed-800);
	motor4(FAN_ZHUAN,MORTOR_START,speed-800);
	moterState=2;
}
void motor_left(int speed)
{
   	motor1(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor2(ZHENG_ZHUAN,MORTOR_START,speed-800);
	moterState=3;
}
void motor_right(int speed)
{
	motor1(FAN_ZHUAN,MORTOR_START,speed-800);
	motor2(FAN_ZHUAN,MORTOR_START,speed-800);
	moterState=4;
}
void motor_stop(void)
{
	motor1(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor2(ZHENG_ZHUAN,MORTOR_STOP,0);	
	motor3(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor4(ZHENG_ZHUAN,MORTOR_STOP,0);
	moterState=0;
}
void motor_stopRightLeft(void)
{
	motor1(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor2(ZHENG_ZHUAN,MORTOR_STOP,0);
}
void motor_stopStraightBack(void)
{
	motor3(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor4(ZHENG_ZHUAN,MORTOR_STOP,0);
}
void motor_leftRound(int angle)//��ת360�ȣ���������ʱ��ʱ330000��������ʱ300000
{
	uint32_t  delayTime;
	delayTime=angle*1667;
	moterState=10;
	//Delay_us(100000);
	motor1(ZHENG_ZHUAN,MORTOR_START,0);
	motor4(ZHENG_ZHUAN,MORTOR_START,0);
	motor2(FAN_ZHUAN,MORTOR_START,0);
  	motor3(FAN_ZHUAN,MORTOR_START,0);
	//
	Delay_us(delayTime);
	motor1(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor2(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor3(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor4(ZHENG_ZHUAN,MORTOR_STOP,0);
}
void motor_leftRound1(void)
{
	motor1(ZHENG_ZHUAN,MORTOR_START,-550);
	motor4(ZHENG_ZHUAN,MORTOR_START,-550);
	motor2(FAN_ZHUAN,MORTOR_START,-550);
  	motor3(FAN_ZHUAN,MORTOR_START,-550);	
}
void motor_rightRound1(void)
{
	motor1(FAN_ZHUAN,MORTOR_START,-550);
	motor4(FAN_ZHUAN,MORTOR_START,-550);
	motor2(ZHENG_ZHUAN,MORTOR_START,-550);
  	motor3(ZHENG_ZHUAN,MORTOR_START,-550);	
}
void motor_rightRound(int angle)//��ת360�ȣ���������ʱ��ʱ330000��������ʱ300000
{
	uint32_t  delayTime;
	delayTime=angle*1667;
	moterState=9;
	//Delay_us(100000);
	motor1(FAN_ZHUAN,MORTOR_START,0);
	motor4(FAN_ZHUAN,MORTOR_START,0);
	motor2(ZHENG_ZHUAN,MORTOR_START,0);
  	motor3(ZHENG_ZHUAN,MORTOR_START,0);

	Delay_us(delayTime);
	motor1(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor2(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor3(ZHENG_ZHUAN,MORTOR_STOP,0);
	motor4(ZHENG_ZHUAN,MORTOR_STOP,0);

}
void motor_rightStraight(int speed)
{
	motor1(FAN_ZHUAN,MORTOR_START,speed-800);
	motor2(FAN_ZHUAN,MORTOR_START,speed-800);
	motor3(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor4(ZHENG_ZHUAN,MORTOR_START,speed-800);
	moterState=5;
}
void motor_leftStraight(int speed)
{
	motor1(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor2(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor3(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor4(ZHENG_ZHUAN,MORTOR_START,speed-800);
	moterState=6;
}
void motor_leftBack(int speed)
{
	motor1(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor2(ZHENG_ZHUAN,MORTOR_START,speed-800);
	motor3(FAN_ZHUAN,MORTOR_START,speed-800);
	motor4(FAN_ZHUAN,MORTOR_START,speed-800);
	moterState=7;
}
void motor_rightBack(int speed)
{
	motor1(FAN_ZHUAN,MORTOR_START,speed-800);
	motor2(FAN_ZHUAN,MORTOR_START,speed-800);
	motor3(FAN_ZHUAN,MORTOR_START,speed-800);
	motor4(FAN_ZHUAN,MORTOR_START,speed-800);
	moterState=8;
}
int process1_1=0;
int count=0;
void moter_1_1(void)
{
	motor1(ZHENG_ZHUAN,MORTOR_START,-550);
	motor4(ZHENG_ZHUAN,MORTOR_START,-550);
	motor2(FAN_ZHUAN,MORTOR_START,-550);
	motor3(FAN_ZHUAN,MORTOR_START,-550);
}
