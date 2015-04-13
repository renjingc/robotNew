#include "function.h"
#include "usart1.h"
#include "stepperMoter.h"

__IO u32 TimeAll = 0;//定义全局时间变量
__IO u32 End_Num = 0;//这套动作最后的数组号
__IO u32 Test_End_Time = 0;
Move_List function_list1[LIST1_NUM];
vu8 DJ_CorrentDuty[12]={DJ1_INIT_DUTY,
						DJ2_INIT_DUTY,
						DJ3_INIT_DUTY,
						DJ4_INIT_DUTY,
						DJ5_INIT_DUTY,
						DJ6_INIT_DUTY,
						DJ7_INIT_DUTY,
						DJ8_INIT_DUTY,
						DJ9_INIT_DUTY,
						DJ10_INIT_DUTY,
						DJ11_INIT_DUTY,
						DJ12_INIT_DUTY
					};

//添加第几个动作，开始时间，结束时间，开始占空比，结束占空比，舵机号。
//动作依次从0 1 2开始直到最大动作数-1（MOVE_NUM_ALL-1）
//开始时间小于结束时间
//占空比对应的值的大小为50-250
//舵机号分别为0 1 2 3 4 5 6	7 8 9 10 11。
void Function_Add_Son(u16 Function_Num, uint32_t Start_Time_t, uint32_t End_Time_t, u8 Start_Duty_t, u8 End_Duty_t, u8 DJ_Num_t )//添加函数的统一封装
{
#ifdef TEST_MODE
	if(Function_Num >= LIST1_NUM || Start_Time_t > End_Time_t || Start_Duty_t < 25 || Start_Duty_t > 125 || End_Duty_t < 25 || End_Duty_t > 125 || DJ_Num_t < 0 || DJ_Num_t > 11)
		while(1);//输入有误，正式程序可以注释掉这个部分
#endif
	function_list1[Function_Num].Start_Time = Start_Time_t ;
	function_list1[Function_Num].End_Time   = End_Time_t ;	
	function_list1[Function_Num].Start_Duty = Start_Duty_t ;
	function_list1[Function_Num].End_Duty   = End_Duty_t ;
	function_list1[Function_Num].DJ_Num     = DJ_Num_t;
	function_list1[Function_Num].add        = ((float)End_Duty_t - (float)Start_Duty_t) / ((float)End_Time_t - (float)Start_Time_t);

	if(Test_End_Time < End_Time_t)
		Test_End_Time = End_Time_t;
	
	printf("#Move:%d , Start Time:%d , End Time:%d , Start Value:%d , EndValue:%d , Server Number:%d \r\n",Function_Num, Start_Time_t, End_Time_t, Start_Duty_t, End_Duty_t, DJ_Num_t);
}

//这个函数为所有添加动作
void Function_Add(void)
{
	u32 num = 0;//用来记录动作数
	int time_add = 0;
	printf("Move List Add Start:\r\n#");
	printf("Move List Add End!\r\n#");	
}
void Function_Init(void)
{
	u32 i;
	for(i=0; i<LIST1_NUM; i++)
	{
	  function_list1[i].Start_Time = 0;
	  function_list1[i].End_Time = 0;
  	  function_list1[i].Start_Duty = 0;
  	  function_list1[i].End_Duty = 0;
  	  function_list1[i].DJ_Num = 0;
  	  function_list1[i].add = 0;
	}
	DJ_CorrentDuty[0]=DJ1_INIT_DUTY;
	DJ_CorrentDuty[1]=DJ2_INIT_DUTY;
	DJ_CorrentDuty[2]=DJ3_INIT_DUTY;
	DJ_CorrentDuty[3]=DJ4_INIT_DUTY;
	DJ_CorrentDuty[4]=DJ5_INIT_DUTY;
	DJ_CorrentDuty[5]=DJ6_INIT_DUTY;
	DJ_CorrentDuty[6]=DJ7_INIT_DUTY;
	DJ_CorrentDuty[7]=DJ8_INIT_DUTY;
	DJ_CorrentDuty[8]=DJ9_INIT_DUTY;
	DJ_CorrentDuty[9]=DJ10_INIT_DUTY;
	DJ_CorrentDuty[10]=DJ11_INIT_DUTY;
	DJ_CorrentDuty[11]=DJ12_INIT_DUTY;
	for(i=0;i<12;i++)
	{
		switch(i)
		{
		case 0:
			TIM_SetCompare1(TIM5,DJ_CorrentDuty[i]);
			break;
		case 1:
			TIM_SetCompare2(TIM5,DJ_CorrentDuty[i]);
			break;
		case 2:
			TIM_SetCompare3(TIM5,DJ_CorrentDuty[i]);
			break;
		case 3:
			TIM_SetCompare4(TIM5,DJ_CorrentDuty[i]);
			break;
		case 4:
			TIM_SetCompare1(TIM1,DJ_CorrentDuty[i]);
			break;
		case 5:
			TIM_SetCompare1(TIM4,DJ_CorrentDuty[i]);
			break;
		case 6:
			TIM_SetCompare2(TIM4,DJ_CorrentDuty[i]);
			break;
		case 7:
			TIM_SetCompare3(TIM4,DJ_CorrentDuty[i]);
			break;
		case 8:
			TIM_SetCompare4(TIM4,DJ_CorrentDuty[i]);
			break;
		case 9:
			TIM_SetCompare2(TIM1,DJ_CorrentDuty[i]);
			break;
		case 10:
			TIM_SetCompare4(TIM1,DJ_CorrentDuty[i]);
			break;
		case 11:
			TIM_SetCompare3(TIM1,DJ_CorrentDuty[i]);
			break;
		default:break;
		}
	}
	printf("#All function has clear!\r\n");
	//Function_Add();
}		
//传入当前时间			   
void Function_Do(u32 time)
{
	u32 function_num;
	float duty_temp;
	for(function_num = 0; function_num<End_Num; function_num++)//在注册的动作中全部查询一遍，可以优化
	{
		if(function_list1[function_num].Start_Time<=time && function_list1[function_num].End_Time>=time)//注册的动作在当前时间内
		{
			duty_temp = function_list1[function_num].add*(time-function_list1[function_num].Start_Time)+function_list1[function_num].Start_Duty;
			switch(function_list1[function_num].DJ_Num)
			{
				case 0:
						TIM_SetCompare1(TIM5,(u8)duty_temp);
						DJ_CorrentDuty[0] = (u8)duty_temp;
						break;
				case 1:
						TIM_SetCompare2(TIM5,(u8)duty_temp);
						DJ_CorrentDuty[1] = (u8)duty_temp;
						break;
				case 2:
						TIM_SetCompare3(TIM5,(u8)duty_temp);
						DJ_CorrentDuty[2] = (u8)duty_temp;
						break;
				case 3:
						TIM_SetCompare4(TIM5,(u8)duty_temp);
						DJ_CorrentDuty[3] = (u8)duty_temp;
						break;
				case 4:
						TIM_SetCompare1(TIM1,(u8)duty_temp);
						DJ_CorrentDuty[4] = (u8)duty_temp;
						break;
				case 5:
						TIM_SetCompare1(TIM4,(u8)duty_temp);
						DJ_CorrentDuty[5] = (u8)duty_temp;
						break;
				case 6:
						TIM_SetCompare2(TIM4,(u8)duty_temp);
						DJ_CorrentDuty[6] = (u8)duty_temp;
						break;
				case 7:
						TIM_SetCompare3(TIM4,(u8)duty_temp);
						DJ_CorrentDuty[7] = (u8)duty_temp;
						break;
				case 8:	
						TIM_SetCompare4(TIM4,(u8)duty_temp);
						DJ_CorrentDuty[8] = (u8)duty_temp;
						break;
				case 9:
						TIM_SetCompare2(TIM1,(u8)duty_temp);
						DJ_CorrentDuty[9] = (u8)duty_temp;
						break;
				case 10:
						TIM_SetCompare4(TIM1,(u8)duty_temp);
						DJ_CorrentDuty[10] = (u8)duty_temp;
						break;	
				case 11:
						TIM_SetCompare3(TIM1,(u8)duty_temp);
						DJ_CorrentDuty[11] = (u8)duty_temp;
						break;
	  		}
    	}
  	}
}
void testAllFunction(void)
{
	TimeAll=0;
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	Function_Do(TimeAll);
}
void displayAllSteer(void)
{
	int i; 
	printf("#All Steer Value Now\r\n");
	for(i=0;i<12;i++)
	{
		printf("#Steer%d:%d\r\n",i,DJ_CorrentDuty[i]);
	}
}
