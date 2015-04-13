/*******************************************************
key驱动文件
PA0--LED1

1.GPIO使用方法 定义一个GPIO_InitTypeDef类型结构体
2.开启GPIOC的外部时钟
3.选择GPIO的引脚
4.选择GPIO的模式
5.选择GPIO的速度
6.设置GPIO,GPIO_SetBits为设1，GPIO_ResetBits为设0

*******************************************************/ 
  
#include "key.h" 

/// 延时函数
static void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启外时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//设置GPIO引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	//引脚模式为上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	//初始化GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//检查是否有按键按下
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*检测是否有键按下*/
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*延时消抖*/
		Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*等待按键释放*/
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
