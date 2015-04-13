
#include "HMC5883.h"
//使用的端口，请按照以下接线
u8 CY;
BYTE BUF[8];                         //接收数据缓存区    
BYTE DEV[3];
uchar ge,shi,bai,qian,wan;           //显示变量
int  dis_data;                       //变量

void delay_us(u32 nus) { 
 u32 temp; 
 SysTick->LOAD = 9*nus; 
 SysTick->VAL=0X00;//清空计数器 
 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源  
 do  { 
  temp=SysTick->CTRL;//读取当前倒计数值 
 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
 SysTick->CTRL=0x00; //关闭计数器
 SysTick->VAL =0X00; //清空计数器 
 } 
void delay_ms(u16 nms) 
{ 
 	u32 temp; 
 	SysTick->LOAD = 9000*nms; 
 	SysTick->VAL=0X00;//清空计数器 
 	SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
 	do
	{ 
 		temp=SysTick->CTRL;//读取当前倒计数值 
 	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达 
  	SysTick->CTRL=0x00; //关闭计数器
  	SysTick->VAL =0X00; //清空计数器 
} 
//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
}
/**************************************
起始信号
**************************************/
void HMC5883_Start()
{
		SDAH;
		SCLH;
    delay_us(5);                 //延时
    SDAL;                   //产生下降沿
    delay_us(5);                 //延时
		SCLL;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void HMC5883_Stop()
{
		SDAL;
		SCLH;
    delay_us(5);                 //延时
    SDAH;
    delay_us(5);                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void HMC5883_SendACK(u8 ack)
{
		if(ack)
		SDAH;
		else
		SDAL;
    SCLH;                    //拉高时钟线
    delay_us(5);                 //延时
    SCLL;                    //拉低时钟线
    delay_us(5);                 //延时
}

/**************************************
接收应答信号
**************************************/
u8 HMC5883_RecvACK()
{
    SCLH;
    delay_us(5);                 //延时
    CY= GPIO_ReadInputDataBit(GPIOB,SDA);                   //读应答信号
    SCLL;                    //拉低时钟线
    delay_us(5);                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void HMC5883_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
			  if(dat>=0x80)
					SDAH;
				else
					SDAL;
        dat <<= 1;              //移出数据的最高位
        SCLH;                //拉高时钟线
        delay_us(5);             //延时
        SCLL;               //拉低时钟线
        delay_us(5);             //延时
    }
    HMC5883_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE HMC5883_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDAH;                  //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCLH;                //拉高时钟线
        delay_us(5);             //延时
        dat |= GPIO_ReadInputDataBit(GPIOB,SDA);             //读数据               
        SCLL;               //拉低时钟线
        delay_us(5);             //延时
    }
    return dat;
}

//***************************************************

void Single_Write_HMC5883(uchar REG_Address,uchar REG_data)
{
    HMC5883_Start();                  //起始信号
    HMC5883_SendByte(SlaveAddress);   //发送设备地址+写信号
    HMC5883_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf 
    HMC5883_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf
    HMC5883_Stop();                   //发送停止信号
}
uchar Single_Read_HMC5883(uchar REG_Address)
{  uchar REG_data;
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress);           //发送设备地址+写信号
    HMC5883_SendByte(REG_Address);                   //发送存储单元地址，从0开始	
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=HMC5883_RecvByte();              //读出寄存器数据
		HMC5883_SendACK(1);   
		HMC5883_Stop();                           //停止信号
    return REG_data; 
}
//******************************************************
//
//连续读出HMC5883内部角度数据，地址范围0x3~0x5
//
//******************************************************
void Multiple_Read_HMC5883(void)
{   uchar i;
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress);           //发送设备地址+写信号
    HMC5883_SendByte(0x03);                   //发送存储单元地址，从0x3开始	
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<7; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = HMC5883_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 6)
        {
           HMC5883_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //回应ACK
       }
   }
    HMC5883_Stop();                          //停止信号
    delay_ms(5);
}
void Dev_Read_HMC5883(void)
{   uchar i;
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress);           //发送设备地址+写信号
    HMC5883_SendByte(0x0a);                   //发送存储单元地址，从0x3开始	
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<4; i++)                      //连续读取6个地址数据，存储中BUF
    {
        DEV[i] = HMC5883_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i ==3)
        {
           HMC5883_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //回应ACK
       }
   }
    HMC5883_Stop();                          //停止信号
    delay_ms(5);
}
//初始化HMC5883，根据需要请参考pdf进行修改****
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
