/*******************************************************
key�����ļ�
PA0--LED1

1.GPIOʹ�÷��� ����һ��GPIO_InitTypeDef���ͽṹ��
2.����GPIOC���ⲿʱ��
3.ѡ��GPIO������
4.ѡ��GPIO��ģʽ
5.ѡ��GPIO���ٶ�
6.����GPIO,GPIO_SetBitsΪ��1��GPIO_ResetBitsΪ��0

*******************************************************/ 
  
#include "key.h" 

/// ��ʱ����
static void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//����GPIO����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	//����ģʽΪ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	//��ʼ��GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//����Ƿ��а�������
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*����Ƿ��м�����*/
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*��ʱ����*/
		Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*�ȴ������ͷ�*/
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			return 	KEY_ON;	 
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}
/*********************************************END OF FILE**********************/
