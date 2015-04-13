#include "time.h"
#include "led.h"


int8_t TIM4CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
uint16_t TIM4CH1_CAPTURE_UPVAL;
uint16_t TIM4CH1_CAPTURE_DOWNVAL;

uint8_t TIM4CH2_CAPTURE_STA = 0;	//ͨ��2���벶���־������λ�������־����6λ�������־		
uint16_t TIM4CH2_CAPTURE_UPVAL;
uint16_t TIM4CH2_CAPTURE_DOWNVAL;

uint8_t TIM4CH3_CAPTURE_STA = 0;	//ͨ��3���벶���־������λ�������־����6λ�������־		
uint16_t TIM4CH3_CAPTURE_UPVAL;
uint16_t TIM4CH3_CAPTURE_DOWNVAL;

uint8_t TIM4CH4_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
uint16_t TIM4CH4_CAPTURE_UPVAL;
uint16_t TIM4CH4_CAPTURE_DOWNVAL;

uint32_t timeUp1 = 0;	//�����ܸߵ�ƽ��ʱ��
uint32_t timeUp2 = 0;	//�����ܸߵ�ƽ��ʱ��
uint32_t timeUp3 = 0;	//�����ܸߵ�ƽ��ʱ��
uint32_t timeUp4 = 0;	//�����ܸߵ�ƽ��ʱ��
uint32_t tim4_T1;
uint32_t tim4_T2;
uint32_t tim4_T3;
uint32_t tim4_T4;
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��2
void Time_Init(uint16_t arr,uint16_t psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = 5000; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
}


//��ʱ��4ͨ��1���벶������
void Time4_Init(uint16_t arr, uint16_t psc)
{
	TIM_ICInitTypeDef TIM4_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��

	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PD12 �������� 
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;  //PB6,8,9 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PB6,7,8,9 ���� 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9);//PB6,8,9  ����

	//��ʼ����ʱ��4 TIM4���ò���������Ҫ��ΪPWM������� 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM4���벶����� ͨ��1
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//��ʼ��TIM4���벶����� ͨ��2
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//��ʼ��TIM4���벶����� ͨ��3
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//��ʼ��TIM4���벶����� ͨ��4
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//�жϷ����ʼ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);   //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4,ENABLE);   //����������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	

	TIM_Cmd(TIM4, ENABLE); 		//ʹ�ܶ�ʱ��4

}

//��ʱ��4�жϷ������,��CH1��Ϊ������ת����ͨ�� ��PB6�˿�
void TIM4_IRQHandler(void)
{
	if ((TIM4CH1_CAPTURE_STA & 0X80) == 0) 		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); 		//����жϱ�־λ
			if (TIM4CH1_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM4CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM4);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM4CH1_CAPTURE_DOWNVAL < TIM4CH1_CAPTURE_UPVAL)
				{/* �����������ʼֵ����ĩβֵ��˵������������� */
					tim4_T1 = 65535;
				}
				else
				tim4_T1 = 0;  
				timeUp1 = TIM4CH1_CAPTURE_DOWNVAL - TIM4CH1_CAPTURE_UPVAL
						+ tim4_T1;		//�õ��ܵĸߵ�ƽ��ʱ��
				//pwmout1 = timeUp1;		//�ܵĸߵ�ƽ��ʱ��
				timeUp1 =timeUp1 *17/1000;//�������&&UltrasonicWave_Distance<85
			
				
				TIM4CH1_CAPTURE_STA = 0;		//�����־λ���㣬��һ������Ҫ��
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM4CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM4);		//��ȡ����������
				TIM4CH1_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM4CH2_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)		//����2���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);		//����жϱ�־λ
			if (TIM4CH2_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM4CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM4);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM4CH2_CAPTURE_DOWNVAL < TIM4CH2_CAPTURE_UPVAL)
				{
					tim4_T2 = 65535;
				}
				else
					tim4_T2 = 0;
				timeUp2 = TIM4CH2_CAPTURE_DOWNVAL - TIM4CH2_CAPTURE_UPVAL
						+ tim4_T2;		//�õ��ܵĸߵ�ƽ��ʱ��
				timeUp2 =timeUp2 *17/1000;//�������&&UltrasonicWave_Distance<85

				TIM4CH2_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM4CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM4);		//��ȡ����������
				TIM4CH2_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM4CH3_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)		//����3���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);		//����жϱ�־λ
			if (TIM4CH3_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM4CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM4);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM4CH3_CAPTURE_DOWNVAL < TIM4CH3_CAPTURE_UPVAL)
				{
					tim4_T3 = 65535;
				}
				else
					tim4_T3 = 0;
				timeUp3 = TIM4CH3_CAPTURE_DOWNVAL - TIM4CH3_CAPTURE_UPVAL
						+ tim4_T3;		//�õ��ܵĸߵ�ƽ��ʱ��
				timeUp3 =timeUp3 *17/1000;//�������&&UltrasonicWave_Distance<85

				TIM4CH3_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM4CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM4);		//��ȡ����������
				TIM4CH3_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM4CH4_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)		//����4���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);		//����жϱ�־λ
			if (TIM4CH4_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM4CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM4);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM4CH4_CAPTURE_DOWNVAL < TIM4CH4_CAPTURE_UPVAL)
				{
					tim4_T4 = 65535;
				}
				else
					tim4_T4 = 0;
				timeUp4 = TIM4CH4_CAPTURE_DOWNVAL - TIM4CH4_CAPTURE_UPVAL
						+ tim4_T4;		//�õ��ܵĸߵ�ƽ��ʱ��
				
				timeUp4 =timeUp4 *17/1000;//�������&&UltrasonicWave_Distance<85

				TIM4CH4_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC4PolarityConfig(TIM4, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM4CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM4);		//��ȡ����������
				TIM4CH4_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC4PolarityConfig(TIM4, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
}



