#include "stepperMoter.h"
#include "delay.h"
extern int sValue[12];

//���� 135��->50		75��㣬109->��ǰ90��
//TIM5
//CH1->PA0	//����
//CH2->PA1  	//����
//CH3->PA2  	//����
//CH4->PA3
void TIM5GPIO_Init(void)
{
 //GPIO A1,A2,A3����
  GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM5 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Tim5_Configuration(void)
{
    //TIM5����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//70Ϊ�м�
	/* PWM�źŵ�ƽ����ֵ */
	u16 CCR1_Val = 75; //���ң������֣���45 0�ȣ�����95,90��    
	u16 CCR2_Val = 75; //ǰ��	 45��ǰ70�ȣ�95����40��	����75����    45��95Լ110��
	u16 CCR3_Val = 75; //D3
	u16 CCR4_Val = 75;
	//u16 CCR4_Val = 70;
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
/* -----------------------------------------------------------------------
    TIM5 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM5CLK = 72 MHz, Prescaler = 0x0, TIM5 counter clock = 72 MHz
    TIM5 ARR Register = 999 => TIM5 Frequency = TIM5 counter clock/(ARR + 1)
    TIM5 Frequency = 72 KHz.
    TIM5 Channel1 duty cycle = (TIM5_CCR1/ TIM5_ARR)* 100 = 50%
    TIM5 Channel2 duty cycle = (TIM5_CCR2/ TIM5_ARR)* 100 = 37.5%
    TIM5 Channel3 duty cycle = (TIM5_CCR3/ TIM5_ARR)* 100 = 25%
    TIM5 Channel4 duty cycle = (TIM5_CCR4/ TIM5_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 1439;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz	   //72kHZ  1439->50hz  4->18khz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC3Init(TIM5, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC4Init(TIM5, &TIM_OCInitStructure);	//ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM5, ENABLE);			 // ʹ��TIM5���ؼĴ���ARR  */

  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);                   //ʹ�ܶ�ʱ��3
	
}
void TIM5_Init(void)
{
	TIM5GPIO_Init();
	Tim5_Configuration();
}

//TIM4
//CH1->PB6	//����
//CH2->PB7	//����
//CH3->PB8	//����
//CH4->PB9
void TIM4GPIO_Init(void)
{
 //GPIO A1,A2,A3����
  GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM5 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7 | GPIO_Pin_8|GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Tim4_Configuration(void)
{
    //TIM5����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//70Ϊ�м�
	/* PWM�źŵ�ƽ����ֵ */
	u16 CCR1_Val = 75; //���ң������֣���45 0�ȣ�����95,90��    
	u16 CCR2_Val = 75; //ǰ��	 45��ǰ70�ȣ�95����40��	����75����    45��95Լ110��
	u16 CCR3_Val = 75; //D3
	u16 CCR4_Val = 75;
	//u16 CCR4_Val = 70;
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
/* -----------------------------------------------------------------------
    TIM5 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM5CLK = 72 MHz, Prescaler = 0x0, TIM5 counter clock = 72 MHz
    TIM5 ARR Register = 999 => TIM5 Frequency = TIM5 counter clock/(ARR + 1)
    TIM5 Frequency = 72 KHz.
    TIM5 Channel1 duty cycle = (TIM5_CCR1/ TIM5_ARR)* 100 = 50%
    TIM5 Channel2 duty cycle = (TIM5_CCR2/ TIM5_ARR)* 100 = 37.5%
    TIM5 Channel3 duty cycle = (TIM5_CCR3/ TIM5_ARR)* 100 = 25%
    TIM5 Channel4 duty cycle = (TIM5_CCR4/ TIM5_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 1439;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz	   //72kHZ  1439->50hz  4->18khz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);	//ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // ʹ��TIM5���ؼĴ���ARR  */

  /* TIM5 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //ʹ�ܶ�ʱ��3
	
}
void TIM4_Init(void)
{
	TIM4GPIO_Init();
	Tim4_Configuration();
}

//TIM1
//TIM1_CH1->PA8
//TIM1_CH2->PA9
//TIM1_CH3->PA10
//TIM1_CH4->PA11

//TIM1�ض�������
//TIM1_CH1->PE9
//TIM1_CH2->PE11
//TIM1_CH3->PE13
//TIM1_CH4->PE14
void TIM1GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
   	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* PA8����Ϊ���ܽ�(PWM) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

}
void Tim1_Configuration(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	u16 CCR1_Val = 75;      //ǰ��ĵ��
 	u16 CCR2_Val = 75;	  	 //����ĵ��
 	u16 CCR3_Val = 75;		 //����ĵ��
 	u16 CCR4_Val = 75;		 //����ĵ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  
     TIM_DeInit(TIM1); //����Ϊȱʡֵ

	/*TIM1ʱ������*/
	TIM_TimeBaseStructure.TIM_Prescaler = 6;      //Ԥ��Ƶ(ʱ�ӷ�Ƶ)72M/4000=18K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 999;       //װ��ֵ 18k/144=125hz ����˵���ϼӵ�144������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //������ʱ�ӷָ� �����ò���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;    //���ڼ�����ֵ �����ò���
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);    //��ʼ��TIMx��ʱ�������λ
	
	/* Channel 1 Configuration in PWM mode ͨ��һ��PWM */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;      //PWMģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //����ͨ����Ч PA8 
	//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //����ͨ��Ҳ��Ч PB13
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;         //ռ��ʱ�� 144 ����40��ʱ��Ϊ�ߣ���������������෴
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������
	//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;    //�����˵ļ��� 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //����״̬�µķǹ���״̬ ����
	//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //�Ȳ���
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);       //����ʼ������TIMxͨ��1����2.0��ΪTIM_OCInit
	
	  /* PWM1 Mode configuration: Channel2 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	  TIM_OC2Init(TIM1, &TIM_OCInitStructure);	  //ʹ��ͨ��2
	  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel3 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	  TIM_OC3Init(TIM1, &TIM_OCInitStructure);	 //ʹ��ͨ��3
	  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel4 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	  TIM_OC4Init(TIM1, &TIM_OCInitStructure);	//ʹ��ͨ��4
	  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/* TIM1 counter enable����ʱ�� */
	TIM_Cmd(TIM1,ENABLE);
	
	/* TIM1 Main Output Enable ʹ��TIM1����������*/
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
void TIM1_Init(void)
{
	TIM1GPIO_Init();
	Tim1_Configuration();
}

//TIM8
//TIM8_CH1->PC6
//TIM8_CH2->PC7
//TIM8_CH3->PC8
//TIM8_CH4->PC9
void TIM8GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* PA8����Ϊ���ܽ�(PWM) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Tim8_Configuration(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	u16 CCR1_Val = 75;      //ǰ��ĵ��
 	u16 CCR2_Val = 75;	  	 //����ĵ��
 	u16 CCR3_Val = 75;		 //����ĵ��
 	u16 CCR4_Val = 75;		 //����ĵ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);

     TIM_DeInit(TIM8); //����Ϊȱʡֵ

	/*TIM1ʱ������*/
	TIM_TimeBaseStructure.TIM_Prescaler = 1439;      //Ԥ��Ƶ(ʱ�ӷ�Ƶ)72M/4000=18K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 999;       //װ��ֵ 18k/144=125hz ����˵���ϼӵ�144������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //������ʱ�ӷָ� �����ò���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;    //���ڼ�����ֵ �����ò���
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);    //��ʼ��TIMx��ʱ�������λ
	
	/* Channel 1 Configuration in PWM mode ͨ��һ��PWM */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;      //PWMģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //����ͨ����Ч PA8 
	//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //����ͨ��Ҳ��Ч PB13
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;         //ռ��ʱ�� 144 ����40��ʱ��Ϊ�ߣ���������������෴
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������
	//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;    //�����˵ļ��� 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //����״̬�µķǹ���״̬ ����
	//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //�Ȳ���
	
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);       //����ʼ������TIMxͨ��1����2.0��ΪTIM_OCInit
	
	  /* PWM1 Mode configuration: Channel2 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	  TIM_OC2Init(TIM8, &TIM_OCInitStructure);	  //ʹ��ͨ��2
	  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel3 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	  TIM_OC3Init(TIM8, &TIM_OCInitStructure);	 //ʹ��ͨ��3
	  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel4 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
	  TIM_OC4Init(TIM8, &TIM_OCInitStructure);	//ʹ��ͨ��4
	  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	/* TIM1 counter enable����ʱ�� */
	TIM_Cmd(TIM8,ENABLE);
	
	/* TIM1 Main Output Enable ʹ��TIM1����������*/
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
}
void TIM8_Init(void)
{
	TIM8GPIO_Init();
	Tim8_Configuration();
}

//����2.5%-12.5%��ռ�ձȵ��� 270������	  PWM����25-125
//һ����7%Ϊ�м�ֵ��4.5%-10%���ҷ�Χ
void stepperMoterInit()
{
	TIM5_Init();//��ߵĵ��ǰ�ĸ�
	TIM8_Init();//������צ���������
	TIM4_Init();//�ұߵĵ��ǰ�ĸ�	  
	TIM1_Init(); 
}
void setAllSteeringEngine(void)
{
	int i;
	for(i=0;i<12;i++)
	{
		switch(i)
		{
		case 0:
			TIM_SetCompare1(TIM5,sValue[i]);
			break;
		case 1:
			TIM_SetCompare2(TIM5,sValue[i]);
			break;
		case 2:
			TIM_SetCompare3(TIM5,sValue[i]);
			break;
		case 3:
			TIM_SetCompare4(TIM5,sValue[i]);
			break;
		case 4:
			TIM_SetCompare1(TIM8,sValue[i]);
			break;
		case 5:
			TIM_SetCompare1(TIM4,sValue[i]);
			break;
		case 6:
			TIM_SetCompare2(TIM4,sValue[i]);
			break;
		case 7:
			TIM_SetCompare3(TIM4,sValue[i]);
			break;
		case 8:
			TIM_SetCompare4(TIM4,sValue[i]);
			break;
		case 9:
			TIM_SetCompare2(TIM8,sValue[i]);
			break;
		case 10:
			TIM_SetCompare3(TIM8,sValue[i]);
			break;
		case 11:
			TIM_SetCompare4(TIM8,sValue[i]);
			break;
		default:break;
		}
	}	
}
