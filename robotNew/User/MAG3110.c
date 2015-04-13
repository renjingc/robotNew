#include "MAG3110.h"
#include "delay.h"

long MAG3110_XOFF=0,MAG3110_YOFF=0;
long MAG3110_XMax=0,MAG3110_YMax=0,MAG3110_XMin=0,MAG3110_YMin=0;
long MAG3110_XData=0,MAG3110_YData=0;
long ang;
/*******************************************************************************
* Function Name  : I2C_Configuration
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void I2C_Configuration(void)
{
   I2C_InitTypeDef  I2C_InitStructure;
   GPIO_InitTypeDef  GPIO_InitStructure; 

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);

   /* Configure I2C2 pins: PB10->SCL and PB11->SDA */
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
		
   I2C_DeInit(I2C2);
   I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
   I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
   I2C_InitStructure.I2C_OwnAddress1 = 0x1C;
   I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
   I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
   I2C_InitStructure.I2C_ClockSpeed = 400000;
    
   I2C_Cmd(I2C2, ENABLE);
   I2C_Init(I2C2, &I2C_InitStructure);

   I2C_AcknowledgeConfig(I2C2, ENABLE);
}
 
/*******************************************************************************
* Function Name  : I2C_delay
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void I2C_delay(uint16_t cnt)
{
	while(cnt--);
}

/*******************************************************************************
* Function Name  : I2C_AcknowledgePolling
* Description    : 
* Input          : I2C_TypeDef * , uint8_t
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,uint8_t I2C_Addr)
{
  vu16 SR1_Tmp;
  do
  {   
    I2C_GenerateSTART(I2Cx, ENABLE);

    SR1_Tmp = I2C_ReadRegister(I2Cx, I2C_Register_SR1);

#ifdef AT24C01A

	I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
#else

	I2C_Send7bitAddress(I2Cx, 0, I2C_Direction_Transmitter);
#endif

  }while(!(I2C_ReadRegister(I2Cx, I2C_Register_SR1) & 0x0002));
  
  I2C_ClearFlag(I2Cx, I2C_FLAG_AF);
    
  I2C_GenerateSTOP(I2Cx, ENABLE);
}


/*******************************************************************************
* Function Name  : I2C_Read
* Description    : 
* Input          : 
* Output         : 
* Return         : 
* Attention		 : None
*******************************************************************************/
uchar I2C_Read(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
 uchar buffer1; 
 

	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
		
	I2C_AcknowledgeConfig(I2Cx, ENABLE);


    I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));


    I2C_Send7bitAddress(I2Cx,  I2C_Addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx, addr);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		

	
    while (num)
    {
		if(num==1)
		{
     		I2C_AcknowledgeConfig(I2Cx, DISABLE);
    		I2C_GenerateSTOP(I2Cx, ENABLE);
		}
	    
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
	  buffer1 = I2C_ReceiveData(I2Cx);
	   // buf++;
	    /* Decrement the read bytes counter */
	    num--;
    }

	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	return buffer1;
}	

/*******************************************************************************
* Function Name  : I2C_WriteOneByte
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
uint8_t I2C_WriteOneByte(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{
  	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
		
//	I2C_AcknowledgeConfig(I2Cx, ENABLE);


    I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));


    I2C_Send7bitAddress(I2Cx,  I2C_Addr, I2C_Direction_Transmitter);
  	    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  	I2C_SendData(I2Cx, addr);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));



  	I2C_SendData(I2Cx, value); 
  	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
  	I2C_GenerateSTOP(I2Cx, ENABLE);
  
  	I2C_AcknowledgePolling(I2Cx,I2C_Addr);

	I2C_delay(1000);

	return 0;
}


/*******************************************************************************
* Function Name  : I2C_Write
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention		 : None
*******************************************************************************/
uint8_t I2C_Write(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
	uint8_t err=0;
	
	while(num--)
	{
		if(I2C_WriteOneByte(I2Cx, I2C_Addr,addr++,*buf++))
		{
			err++;
		}
	}
	if(err)
		return 1;
	else 
		return 0;	
}
/*********************************************************\
* Put MAG3110Q into Active Mode
\*********************************************************/
void MAG3110_Active ()
{
  byte n;
  n = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,CTRL_REG1,0,1);
  I2C_WriteOneByte(I2C2,MAG3110_IIC_ADDRESS,CTRL_REG1,n&0XFC|ACTIVE_MASK);
}

/*********************************************************\
* Put MAG3110Q into Standby Mode
\*********************************************************/
void MAG3110_Standby (void)
{
  byte n;

  n = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,CTRL_REG1,0,1);
   I2C_WriteOneByte(I2C2,MAG3110_IIC_ADDRESS,CTRL_REG1, n&0xFC|STANDBY_MASK);
}

/*********************************************************\
* Initialize MAG3110Q
\*********************************************************/
void MAG3110_Init (void)
{  
  MAG3110_Standby();   
  I2C_WriteOneByte(I2C2,MAG3110_IIC_ADDRESS,CTRL_REG1, DATA_RATE_5MS);    
  MAG3110_Active();
}
long MAG3110_DataProcess (int MAG3110_XData,int MAG3110_YData)
{
	uint16_t MAG3110_Ang;
	/*MAG3110_XData -= MAG3110_XOFF;
	MAG3110_YData -= MAG3110_YOFF;
	if (MAG3110_XData == 0)
	{
		if (MAG3110_YData>0)
		{
			MAG3110_Ang= 90;
		}
		else
		{
			MAG3110_Ang= 270;
		}
	}
	else if (MAG3110_YData == 0)
	{
		if (MAG3110_XData>0)
		{
			MAG3110_Ang= 0;
		}
		else
		{
			MAG3110_Ang= 180;
		}
	}
	else if ((MAG3110_XData > 0) && (MAG3110_YData > 0))
	{
		MAG3110_Ang = (atan ( ( (float)MAG3110_YData) / ( (float) MAG3110_XData ) ) )* 180 / 3.14;
	}
	else if ((MAG3110_XData < 0) && (MAG3110_YData > 0))
	{
		MAG3110_XData = -MAG3110_XData;
		MAG3110_Ang = 180-(atan ( ( (float)MAG3110_YData) / ( (float)MAG3110_XData ) ) ) * 180 / 3.14;
	}
	else if ((MAG3110_XData < 0) && (MAG3110_YData < 0))
	{
		MAG3110_XData = -MAG3110_XData;
		MAG3110_YData = -MAG3110_YData;
		MAG3110_Ang = (atan ( ( (float)MAG3110_YData) / ( (float) MAG3110_XData ) ) )* 180 / 3.14 + 180;
	}
	else if ((MAG3110_XData > 0) && (MAG3110_YData < 0))
	{
		MAG3110_YData = -MAG3110_YData;
		MAG3110_Ang = 360-(atan ( ( (float)MAG3110_YData) / ( (float)MAG3110_XData ) ) ) * 180 / 3.14;
	} */
	if(MAG3110_XData>0x7fff)MAG3110_XData-=0xffff;	  
    if(MAG3110_YData>0x7fff)MAG3110_YData-=0xffff;	  
    MAG3110_Ang= atan2(MAG3110_YData,MAG3110_XData) * (180 / 3.14159265) + 180; // angle in degrees

	return 	 MAG3110_Ang;
}


/*************************************************************************/
void MAG3110_STD(void)
// 此函数需多次执行以保证旋转一圈中
{
// 能够采集到真实的最大值和最小值
	tword wx, wy, wz; 
	//static   uint8_t	First_Flag=0;
	wx.mbyte.hi = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,OUT_X_MSB_REG,0,1); //读取X轴高字节
	wx.mbyte.lo = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,OUT_X_LSB_REG,0,1);//读取X轴低字节
	wy.mbyte.hi = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,OUT_Y_MSB_REG,0,1);//读取Y轴高字节
	wy.mbyte.lo = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,OUT_Y_LSB_REG,0,1);	//读取Y轴低字节
	wz.mbyte.hi = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,OUT_Z_MSB_REG,0,1);//读取Z轴高字节
	wz.mbyte.lo = I2C_Read(I2C2,MAG3110_IIC_ADDRESS,OUT_Z_LSB_REG,0,1);	 //读取Z轴低字节
	printf("X:%d  ",wx.mbyte.hi*256+wx.mbyte.lo);
	printf("Y:%d  ",wy.mbyte.hi*256+wy.mbyte.lo);
	printf("Z:%d  ",wz.mbyte.hi*256+wz.mbyte.lo);
	
	
	MAG3110_XData=wx.mbyte.hi*256+wx.mbyte.lo;
	MAG3110_YData=wy.mbyte.hi*256+wy.mbyte.lo;
	
    

	/*if (!First_Flag)
	{
		MAG3110_XMax = MAG3110_XData;
		MAG3110_XMin = MAG3110_XData;
		MAG3110_YMax = MAG3110_YData;
		MAG3110_YMin = MAG3110_YData;
		First_Flag = 1;
	}
	if (MAG3110_XData > MAG3110_XMax)
	{
		MAG3110_XMax =  MAG3110_XData;
	}
	else if (MAG3110_XData < MAG3110_XMin)
	{
		MAG3110_XMin =  MAG3110_XData;
	}
	if (MAG3110_YData > MAG3110_YMax)
	{
		MAG3110_YMax =  MAG3110_YData;
	}
	else if (MAG3110_YData < MAG3110_YMin)
	{
		MAG3110_YMin =  MAG3110_YData;
	}  
	MAG3110_XOFF = (MAG3110_XMax + MAG3110_XMin) / 2;
	MAG3110_YOFF = (MAG3110_YMax + MAG3110_YMin) / 2; */
	MAG3110_XOFF=MAG3110_XData;
	MAG3110_YOFF=MAG3110_YData;
    /*printf("\r\nMAG3110_XMax：%d ",MAG3110_XMax);
	printf("MAG3110_XMin：%d\r\n",MAG3110_XMin);
    printf("MAG3110_XOFF：%d\r\n",MAG3110_XOFF);

    printf("\r\nMAG3110_YMax：%d  ",MAG3110_YMax);
	printf("MAG3110_YMin：%d\r\n ",MAG3110_YMin);
    printf("AG3110_YOFF：%d\r\n",MAG3110_YOFF);	 */

	ang=MAG3110_DataProcess(wx.mbyte.hi*256+wx.mbyte.lo,wy.mbyte.hi*256+wy.mbyte.lo);
}
void MAG3110_Read()
{
	 uchar i;
	    i=I2C_Read(I2C2,MAG3110_IIC_ADDRESS,STATUS_00_REG,0,1); 
		if(i&ZYXDR_MASK) //数据就绪
		{ 	
			MAG3110_STD(); //读取MAG3110数据，标定中值，数据处理
			//printf("The data needs to be calibrated, turning a lap");
			//printf("\r\n\r\n");
			printf("\r\nPoint to the south angle：%d°\r\n",ang);
		}
		else //数据未就绪
		{
			printf("ID Failed!\n");
		}
		Delay_ms(100);	
}

