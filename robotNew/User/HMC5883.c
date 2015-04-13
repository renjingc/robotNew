
#include "HMC5883.h"
//ʹ�õĶ˿ڣ��밴�����½���
u8 CY;
BYTE BUF[8];                         //�������ݻ�����    
BYTE DEV[3];
uchar ge,shi,bai,qian,wan;           //��ʾ����
int  dis_data;                       //����

void delay_us(u32 nus) { 
 u32 temp; 
 SysTick->LOAD = 9*nus; 
 SysTick->VAL=0X00;//��ռ����� 
 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ  
 do  { 
  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ 
 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
 SysTick->CTRL=0x00; //�رռ�����
 SysTick->VAL =0X00; //��ռ����� 
 } 
void delay_ms(u16 nms) 
{ 
 	u32 temp; 
 	SysTick->LOAD = 9000*nms; 
 	SysTick->VAL=0X00;//��ռ����� 
 	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
 	do
	{ 
 		temp=SysTick->CTRL;//��ȡ��ǰ������ֵ 
 	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽�� 
  	SysTick->CTRL=0x00; //�رռ�����
  	SysTick->VAL =0X00; //��ռ����� 
} 
//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    ge=temp_data+0x30; 	
}
/**************************************
��ʼ�ź�
**************************************/
void HMC5883_Start()
{
		SDAH;
		SCLH;
    delay_us(5);                 //��ʱ
    SDAL;                   //�����½���
    delay_us(5);                 //��ʱ
		SCLL;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void HMC5883_Stop()
{
		SDAL;
		SCLH;
    delay_us(5);                 //��ʱ
    SDAH;
    delay_us(5);                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void HMC5883_SendACK(u8 ack)
{
		if(ack)
		SDAH;
		else
		SDAL;
    SCLH;                    //����ʱ����
    delay_us(5);                 //��ʱ
    SCLL;                    //����ʱ����
    delay_us(5);                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
u8 HMC5883_RecvACK()
{
    SCLH;
    delay_us(5);                 //��ʱ
    CY= GPIO_ReadInputDataBit(GPIOB,SDA);                   //��Ӧ���ź�
    SCLL;                    //����ʱ����
    delay_us(5);                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void HMC5883_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
			  if(dat>=0x80)
					SDAH;
				else
					SDAL;
        dat <<= 1;              //�Ƴ����ݵ����λ
        SCLH;                //����ʱ����
        delay_us(5);             //��ʱ
        SCLL;               //����ʱ����
        delay_us(5);             //��ʱ
    }
    HMC5883_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE HMC5883_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDAH;                  //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCLH;                //����ʱ����
        delay_us(5);             //��ʱ
        dat |= GPIO_ReadInputDataBit(GPIOB,SDA);             //������               
        SCLL;               //����ʱ����
        delay_us(5);             //��ʱ
    }
    return dat;
}

//***************************************************

void Single_Write_HMC5883(uchar REG_Address,uchar REG_data)
{
    HMC5883_Start();                  //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    HMC5883_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    HMC5883_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
    HMC5883_Stop();                   //����ֹͣ�ź�
}
uchar Single_Read_HMC5883(uchar REG_Address)
{  uchar REG_data;
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    HMC5883_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=HMC5883_RecvByte();              //�����Ĵ�������
		HMC5883_SendACK(1);   
		HMC5883_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
//******************************************************
//
//��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
//
//******************************************************
void Multiple_Read_HMC5883(void)
{   uchar i;
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    HMC5883_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<7; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = HMC5883_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 6)
        {
           HMC5883_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //��ӦACK
       }
   }
    HMC5883_Stop();                          //ֹͣ�ź�
    delay_ms(5);
}
void Dev_Read_HMC5883(void)
{   uchar i;
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    HMC5883_SendByte(0x0a);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<4; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        DEV[i] = HMC5883_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i ==3)
        {
           HMC5883_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //��ӦACK
       }
   }
    HMC5883_Stop();                          //ֹͣ�ź�
    delay_ms(5);
}
//��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�****
void Init_HMC5883()
{
  	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
		   | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
		   | RCC_APB2Periph_AFIO, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
  	GPIO_Init(GPIOB,&GPIO_InitStructure); 

    Single_Write_HMC5883(0x02,0x00);  //
	 Single_Write_HMC5883(0x01,0xE0);  //
}
void self_test()
{
	  Single_Write_HMC5883(0x00,0x01);  //
		Single_Write_HMC5883(0x01,0xE0);  //
	  Single_Write_HMC5883(0x02,0x01);  //
}
