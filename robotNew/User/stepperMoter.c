#include "stepperMoter.h"
#include "delay.h"
extern int sValue[12];

//大舵机 135度->50		75零点，109->向前90度
//TIM5
//CH1->PA0	//大舵机
//CH2->PA1  	//大舵机
//CH3->PA2  	//大舵机
//CH4->PA3
void TIM5GPIO_Init(void)
{
 //GPIO A1,A2,A3设置
  GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM5 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Tim5_Configuration(void)
{
    //TIM5设置
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//70为中间
	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 75; //左右，在左手，左45 0度，起来95,90度    
	u16 CCR2_Val = 75; //前后	 45往前70度，95往后40度	正中75左右    45到95约110度
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
  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 1439;	    //设置预分频：不预分频，即为72MHz	   //72kHZ  1439->50hz  4->18khz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
  TIM_OC3Init(TIM5, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
  TIM_OC4Init(TIM5, &TIM_OCInitStructure);	//使能通道4
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM5, ENABLE);			 // 使能TIM5重载寄存器ARR  */

  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);                   //使能定时器3
	
}
void TIM5_Init(void)
{
	TIM5GPIO_Init();
	Tim5_Configuration();
}

//TIM4
//CH1->PB6	//大舵机
//CH2->PB7	//大舵机
//CH3->PB8	//大舵机
//CH4->PB9
void TIM4GPIO_Init(void)
{
 //GPIO A1,A2,A3设置
  GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM5 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7 | GPIO_Pin_8|GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Tim4_Configuration(void)
{
    //TIM5设置
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//70为中间
	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 75; //左右，在左手，左45 0度，起来95,90度    
	u16 CCR2_Val = 75; //前后	 45往前70度，95往后40度	正中75左右    45到95约110度
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
  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 1439;	    //设置预分频：不预分频，即为72MHz	   //72kHZ  1439->50hz  4->18khz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);	//使能通道4
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);			 // 使能TIM5重载寄存器ARR  */

  /* TIM5 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //使能定时器3
	
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

//TIM1重定义引脚
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

    /* PA8设置为功能脚(PWM) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

}
void Tim1_Configuration(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	u16 CCR1_Val = 75;      //前面的电机
 	u16 CCR2_Val = 75;	  	 //后面的电机
 	u16 CCR3_Val = 75;		 //左面的电机
 	u16 CCR4_Val = 75;		 //右面的电机
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);  
     TIM_DeInit(TIM1); //重设为缺省值

	/*TIM1时钟配置*/
	TIM_TimeBaseStructure.TIM_Prescaler = 6;      //预分频(时钟分频)72M/4000=18K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_Period = 999;       //装载值 18k/144=125hz 就是说向上加的144便满了
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置了时钟分割 不懂得不管
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;    //周期计数器值 不懂得不管
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);    //初始化TIMx的时间基数单位
	
	/* Channel 1 Configuration in PWM mode 通道一的PWM */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;      //PWM模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //正向通道有效 PA8 
	//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //反向通道也有效 PB13
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;         //占空时间 144 中有40的时间为高，互补的输出正好相反
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性
	//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;    //互补端的极性 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //空闲状态下的非工作状态 不管
	//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //先不管
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);       //数初始化外设TIMx通道1这里2.0库为TIM_OCInit
	
	  /* PWM1 Mode configuration: Channel2 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
	  TIM_OC2Init(TIM1, &TIM_OCInitStructure);	  //使能通道2
	  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel3 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
	  TIM_OC3Init(TIM1, &TIM_OCInitStructure);	 //使能通道3
	  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel4 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
	  TIM_OC4Init(TIM1, &TIM_OCInitStructure);	//使能通道4
	  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/* TIM1 counter enable开定时器 */
	TIM_Cmd(TIM1,ENABLE);
	
	/* TIM1 Main Output Enable 使能TIM1外设的主输出*/
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

    /* PA8设置为功能脚(PWM) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Tim8_Configuration(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	u16 CCR1_Val = 75;      //前面的电机
 	u16 CCR2_Val = 75;	  	 //后面的电机
 	u16 CCR3_Val = 75;		 //左面的电机
 	u16 CCR4_Val = 75;		 //右面的电机
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);

     TIM_DeInit(TIM8); //重设为缺省值

	/*TIM1时钟配置*/
	TIM_TimeBaseStructure.TIM_Prescaler = 1439;      //预分频(时钟分频)72M/4000=18K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_Period = 999;       //装载值 18k/144=125hz 就是说向上加的144便满了
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置了时钟分割 不懂得不管
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;    //周期计数器值 不懂得不管
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);    //初始化TIMx的时间基数单位
	
	/* Channel 1 Configuration in PWM mode 通道一的PWM */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;      //PWM模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //正向通道有效 PA8 
	//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //反向通道也有效 PB13
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;         //占空时间 144 中有40的时间为高，互补的输出正好相反
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性
	//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;    //互补端的极性 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //空闲状态下的非工作状态 不管
	//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //先不管
	
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);       //数初始化外设TIMx通道1这里2.0库为TIM_OCInit
	
	  /* PWM1 Mode configuration: Channel2 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
	  TIM_OC2Init(TIM8, &TIM_OCInitStructure);	  //使能通道2
	  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel3 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
	  TIM_OC3Init(TIM8, &TIM_OCInitStructure);	 //使能通道3
	  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	  /* PWM1 Mode configuration: Channel4 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
	  TIM_OC4Init(TIM8, &TIM_OCInitStructure);	//使能通道4
	  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	/* TIM1 counter enable开定时器 */
	TIM_Cmd(TIM8,ENABLE);
	
	/* TIM1 Main Output Enable 使能TIM1外设的主输出*/
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
}
void TIM8_Init(void)
{
	TIM8GPIO_Init();
	Tim8_Configuration();
}

//大舵机2.5%-12.5%满占空比调节 270度左右	  PWM设置25-125
//一般舵机7%为中间值，4.5%-10%左右范围
void stepperMoterInit()
{
	TIM5_Init();//左边的电机前四个
	TIM8_Init();//用于手爪的吸力电机
	TIM4_Init();//右边的电机前四个	  
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
