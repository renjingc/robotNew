/******************************************************
USART1��ʼ��
PA9--TX1
PA10--RX1

1.��ʼ��Tx,Rx��IO��,��Ҫ����ģʽ txΪ�����������
																 rxΪ��������ģʽ
2.����USART
	1.���ò�����
	2.�����ֳ�
	3.����ֹͣ
	4.������żУ��λ
	5.�����Ƿ����Ӳ����
	6.����Ϊģʽ
3.��USART�Ĵ�����д������
4.ʹ��USART
******************************************************/
#include "usart1.h"

void USART1GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//����IO��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//txΪ�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//rxΪ��������ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
}
//USART1��ʼ��
void USART1_Config(void)
{

	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//����USART1
	USART_InitStructure.USART_BaudRate=115200;//���ò�����Ϊ115200��
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//�����ֳ�
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//����ֹͣλΪ1λ
	USART_InitStructure.USART_Parity=USART_Parity_No;//��������żУ��λ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//���ò�����Ӳ����
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//����Ϊȫ˫��ģʽ
	USART_Init(USART1,&USART_InitStructure);//��USART�Ĵ�����д������
	//���Ҫʹ��USART1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);//ʹ��USART1
	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void USART1_Init(void)
{
	USART1GPIO_Init();
	USART1_Config();	
}
/// ����USART1�ж�
//void NVIC_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure; 
//	/* Configure the NVIC Preemption Priority Bits */  
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	
//	/* Enable the USARTy Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
/// �ض���c�⺯��printf��USART1
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽڵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/// �ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		/*�ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
/*******************************************************************************
* Description: ����1����һ���ֽ�
*******************************************************************************/
uint8_t USART1_send_char(uint8_t ch)
{
  // Write a character to the USART 
  USART_SendData(USART1, (uint8_t) ch); 
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  return ch;
}
/******************************************************ss*************************
* Description: ����1��������
*******************************************************************************/
void USART1_send_data(uint8_t * buf , u16 len)
{
  u16 i;
  for(i=0;i<len;i++)
  {
    USART1_send_char(*buf);
    buf++;
  }
}
