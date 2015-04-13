#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f10x.h"

#define LIST1_NUM         50			//动作一得最大动作数

#define DJ1_INIT_DUTY     75
#define DJ2_INIT_DUTY     78
#define DJ3_INIT_DUTY     75
#define DJ4_INIT_DUTY     75
#define DJ5_INIT_DUTY     75
#define DJ6_INIT_DUTY     75
#define DJ7_INIT_DUTY     75
#define DJ8_INIT_DUTY     75
#define DJ9_INIT_DUTY     75
#define DJ10_INIT_DUTY    75
#define DJ11_INIT_DUTY    75
#define DJ12_INIT_DUTY    75
/*
 * 舵机编号
 * 共12个舵机
 * 从右手到左手再到头
 * 右肩前后->0 右肩左右->1 右肘->2 右手腕->3 右手爪->4
 * 左肩前后->5 左肩左右->6 左肘->7 左手腕->8 左手爪->9
 * 头左右旋转->10 头前后点头->11
 */

//动作列表结构体
typedef struct
{
  	uint32_t Start_Time; //舵机开始时间            
	uint32_t End_Time; 	 //舵机结束时间
	u8 Start_Duty;		 //舵机开始的PWM
	u8 End_Duty;		 //舵机结束的PWM
	u8 DJ_Num;			 //舵机号	
	float add;			 //舵机占空比于时间的比例，add*(当前时间-该舵机开始时间)+舵机启动PWM
}Move_List;

extern __IO u32 TimeAll;						//全局时间，在系统时钟中会递增
extern __IO u32 End_Num;						//这套动作最后后的数组号
extern Move_List function_list1[LIST1_NUM];		//动作1列表

//给单个舵机加列表函数
void Function_Add_Son(uint16_t Function_Num,uint32_t Start_Time_t, uint32_t End_Time_t, u8 Start_Duty_t, u8 End_Duty_t, u8 DJ_Num_t);
void Function_Add_All(void);//给全部舵机添加全部动作
void Function_Init(void);
void Function_Do(u32 time);
void steerMoter1(int delay);
void testAllFunction(void);
void displayAllSteer(void);
#endif
