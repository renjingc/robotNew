/******************************************************
USART1初始化
PA9--TX1
PA10--RX1

1.初始化Tx,Rx的IO口,主要设置模式 tx为复用推挽输出
																 rx为浮空输入模式
2.配置USART
	1.设置波特率
	2.设置字长
	3.配置停止
	4.设置奇偶校验位
	5.配置是否采用硬件流
	6.设置为模式
3.向USART寄存器中写入配置
4.使能USART
******************************************************/
#include "usart1.h"

void USART1GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//配置IO口
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//tx为复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//rx为浮空输入模式
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
}
//USART1初始化
void USART1_Config(void)
{

	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	//配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//配置USART1
	USART_InitStructure.USART_BaudRate=115200;//设置波特率为115200；
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//设置字长
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//配置停止位为1位
	USART_InitStructure.USART_Parity=USART_Parity_No;//设置无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//配置不采用硬件流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//设置为全双工模式
	USART_Init(USART1,&USART_InitStructure);//向USART寄存器中写入配置
	//如果要使能USART1接受中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);//使能USART1
	
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
/// 配置USART1中断
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
/// 重定义c库函数printf到USART1
int fputc(int ch, FILE *f)
{
		/* 发送一个字节到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/// 重定义c库函数scanf到USART1
int fgetc(FILE *f)
{
		/*等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
/*******************************************************************************
* Description: 串口1发送一个字节
*******************************************************************************/
uint8_t USART1_send_char(uint8_t ch)
{
  // Write a character to the USART 
  USART_SendData(USART1, (uint8_t) ch); 
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  return ch;
}
/******************************************************ss*************************
* Description: 串口1发送数据
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
