#ifndef __HMC5883_H_
#define __HMC5883_H_
#include "stm32f10x.h"

//*********************************************************
#define	SCL GPIO_Pin_6      //IIC时钟引脚定义
#define SDA GPIO_Pin_7    //IIC数据引脚定义
#define SCLL GPIO_ResetBits(GPIOB,SCL)
#define SCLH GPIO_SetBits(GPIOB,SCL)
#define SDAL GPIO_ResetBits(GPIOB,SDA)
#define SDAH GPIO_SetBits(GPIOB,SDA)
#define   uchar unsigned char
#define   uint  unsigned int	
#define	SlaveAddress   0x3C	  //定义器件5883在IIC总线中的从地址
typedef unsigned char BYTE;
typedef unsigned short WORD;
void conversion(uint temp_data);  
void HMC5883_Start(void);
void HMC5883_Stop(void);
void HMC5883_SendACK(u8 ack);
u8 HMC5883_RecvACK(void);
void HMC5883_SendByte(BYTE dat);
BYTE HMC5883_RecvByte(void);
void Single_Write_HMC5883(uchar REG_Address,uchar REG_data);
uchar Single_Read_HMC5883(uchar REG_Address);
void Multiple_Read_HMC5883(void);
void Init_HMC5883(void);
void Dev_Read_HMC5883(void);
void self_test(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);
#endif
